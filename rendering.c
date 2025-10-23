/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:54 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:33:55 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_vertical_line(t_data *data, int ray, const double perp_wall_dist)
{
	const double	wall_height = data->value.proj_plane / perp_wall_dist;
	const int		wall_start = get_wall_start(wall_height);
	const int		wall_end = get_wall_end(wall_start, wall_height);
	const int		tex_x = get_texture_x(data, perp_wall_dist);
	int				y;

	y = 0;
	while (y < wall_start)
	{
		fill_image_buffer(data->image, y, ray, data->surface[CEILING]);
		y++;
	}
	while (y < wall_end)
	{
		fill_image_buffer(data->image, y, ray,
			get_texture_color(data, y, wall_height, tex_x));
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		fill_image_buffer(data->image, y, ray, data->surface[FLOOR]);
		y++;
	}
}

static void	draw_crosshair(t_data *data)
{
	int	y;
	int	x;

	y = -2;
	while (++y < 1)
	{
		x = -6;
		while (++x < 5)
		{
			fill_image_buffer(data->image, data->image.half_height + y,
				data->image.half_width + x, COLOR_CROSSHAIR);
		}
	}
	x = -2;
	while (++x < 1)
	{
		y = -6;
		while (++y < 5)
		{
			fill_image_buffer(data->image, data->image.half_height + y,
				data->image.half_width + x, COLOR_CROSSHAIR);
		}
	}
}

static void	copy_minimap_to_image(t_data *data)
{
	int		i;
	int		j;
	char	*pixel_index;
	int		color;

	fill_image_buffer(data->minimap,
		data->minimap.half_height, data->minimap.half_width, COLOR_PLAYER);
	i = 0;
	while (i < data->minimap.height)
	{
		j = 0;
		while (j < data->minimap.width)
		{
			pixel_index = data->minimap.address
				+ (i * data->minimap.size_line)
				+ (j * data->minimap.bytes_per_pixel);
			color = *(int *)pixel_index;
			fill_image_buffer(data->image,
				MINIMAP_POS_Y + i, MINIMAP_POS_X + j, color);
			j++;
		}
		i++;
	}
}

void	render_game(t_data *data)
{
	if (data->minimap_toggle)
		draw_minimap_grid(data);
	if (data->flashlight_toggle)
		data->apply_darkness = true;
	raycasting(data);
	data->apply_darkness = false;
	if (data->minimap_toggle)
		copy_minimap_to_image(data);
	draw_crosshair(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.buffer, 0, 0);
	data->render_required = false;
}
