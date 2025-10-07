#include "header.h"

int	get_texture_x(t_data *data, const double perp_wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (data->ray.wall_hit == EAST || data->ray.wall_hit == WEST)
		wall_x = data->player.y + perp_wall_dist * data->ray.y_vector;
	else
		wall_x = data->player.x + perp_wall_dist * data->ray.x_vector;
	if (wall_x < 0)
		wall_x *= -1;
	wall_x = wall_x - (int)wall_x;
	tex_x = (int)(wall_x * data->textures[data->ray.wall_hit].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->textures[data->ray.wall_hit].width)
		tex_x = data->textures[data->ray.wall_hit].width - 1;
	return (tex_x * data->textures[data->ray.wall_hit].bytes_per_pixel);
}

int	get_texture_y(t_data *data, const int y, const int wall_height)
{
	const int	d = y * 256 - WINDOW_HEIGHT * 128 + wall_height * 128;
	int			tex_y;

	tex_y = ((d * data->textures[data->ray.wall_hit].height) / wall_height) / 256; //signed integer overflow
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= data->textures[data->ray.wall_hit].height)
		tex_y = data->textures[data->ray.wall_hit].height - 1;
	return (tex_y * data->textures[data->ray.wall_hit].size_line);
}

int	get_wall_start(const int wall_height)
{
	int	wall_start;

	wall_start = (WINDOW_HEIGHT - wall_height) / 2;
	if (wall_start < 0)
		wall_start = 0;
	return (wall_start);
}

int	get_wall_end(const int wall_start, const int wall_height)
{
	int	wall_end;

	wall_end = wall_start + wall_height;
	if (wall_end >= WINDOW_HEIGHT || wall_end < 0)
		wall_end = WINDOW_HEIGHT;
	return (wall_end);
}

int	get_texture_color(t_data *data,
	const int y, const int wall_height, const int tex_x)
{
	const char	*pixel_index = data->textures[data->ray.wall_hit].address
		+ get_texture_y(data, y, wall_height) + tex_x;
	const int	color = *(int *)pixel_index;

	return (color);
}

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

void	draw_crosshair(t_data *data)
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
