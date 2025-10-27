/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:51 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/24 19:46:49 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	calculate_and_assign_ray_values(t_data *data,
	int ray, int *y, int *x)
{
	data->ray.y_vector = data->player.direction_sin
		+ data->value.ray_direction_x[ray] * data->player.direction_right_sin;
	data->ray.x_vector = data->player.direction_cos
		+ data->value.ray_direction_x[ray] * data->player.direction_right_cos;
	data->ray.y = data->player.y;
	data->ray.x = data->player.x;
	*y = (int)data->ray.y;
	*x = (int)data->ray.x;
}

static void	calculate_raycasting_values(t_data *data)
{
	data->player.direction_sin = sin(data->player.direction_in_radians);
	data->player.direction_cos = cos(data->player.direction_in_radians);
	data->player.direction_right_sin
		= sin((data->player.direction + 90) * PI_180);
	data->player.direction_right_cos
		= cos((data->player.direction + 90) * PI_180);
}

static double	get_perp_wall_dist(t_data *data)
{
	const double	delta_x = data->ray.x - data->player.x;
	const double	delta_y = data->ray.y - data->player.y;

	return (delta_x * data->player.direction_cos
		+ delta_y * data->player.direction_sin);
}

static void	dda(t_data *data, int *y, int *x)
{
	while (!is_wall(data, *y, *x))
	{
		calculate_next_grid_distance(data, y, x);
		if (data->minimap_toggle && data->ray_toggle)
			fill_image_buffer(data->minimap, data->minimap.half_height
				+ (int)((data->ray.y - data->player.y)
					* data->value.scaled_grid_size),
				data->minimap.half_width
				+ (int)((data->ray.x - data->player.x)
					* data->value.scaled_grid_size), COLOR_RAY);
	}
}

void	raycasting(t_data *data)
{
	int		ray;
	int		y;
	int		x;

	ray = 0;
	calculate_raycasting_values(data);
	while (ray < WINDOW_WIDTH)
	{
		calculate_and_assign_ray_values(data, ray, &y, &x);
		dda(data, &y, &x);
		if (is_closed_door(data, y, x))
			data->current_texture
				= &data->animation[DOOR].texture[data->animation[DOOR].index];
		else
			data->current_texture = &data->animation[data->ray.wall_hit]
				.texture[data->animation[data->ray.wall_hit].index];
		if (data->minimap_toggle && !data->ray_toggle)
			draw_minimap_ray(data);
		draw_vertical_line(data, ray, get_perp_wall_dist(data));
		ray++;
	}
}
