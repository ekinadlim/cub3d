#include "header.h"

void	calculate_and_assign_ray_values(t_data *data, int ray, int *y, int *x)
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

void	update_y_coordinate_and_wall_hit(t_data *data, int *y)
{
	if (data->ray.y_vector > 0)
	{
		(*y)++;
		data->ray.wall_hit = SOUTH;
	}
	else
	{
		(*y)--;
		data->ray.wall_hit = NORTH;
	}
}

void	update_x_coordinate_and_wall_hit(t_data *data, int *x)
{
	if (data->ray.x_vector > 0)
	{
		(*x)++;
		data->ray.wall_hit = EAST;
	}
	else
	{
		(*x)--;
		data->ray.wall_hit = WEST;
	}
}

void	move_ray(t_data *data, int *y, int *x)
{
	if (data->ray.next_y_grid_distance < data->ray.next_x_grid_distance)
	{
		data->ray.y += data->ray.next_y_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_y_grid_distance * data->ray.x_vector;
		update_y_coordinate_and_wall_hit(data, y);
	}
	else
	{
		data->ray.y += data->ray.next_x_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_x_grid_distance * data->ray.x_vector;
		update_x_coordinate_and_wall_hit(data, x);
	}
}

static void	calculate_next_grid_distance(t_data *data, int *y, int *x)
{
	if (data->ray.y_vector == 0)
		data->ray.next_y_grid_distance = 9999;
	else if (data->ray.y_vector > 0)
		data->ray.next_y_grid_distance
			= ((*y) + 1 - data->ray.y) / data->ray.y_vector;
	else
		data->ray.next_y_grid_distance
			= (data->ray.y - (*y)) / (-data->ray.y_vector);
	if (data->ray.x_vector == 0)
		data->ray.next_x_grid_distance = 9999;
	else if (data->ray.x_vector > 0)
		data->ray.next_x_grid_distance
			= ((*x) + 1 - data->ray.x) / data->ray.x_vector;
	else
		data->ray.next_x_grid_distance
			= (data->ray.x - (*x)) / (-data->ray.x_vector);
	move_ray(data, y, x);
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

double	get_perp_wall_dist(t_data *data) //in rendering?
{
	const double	delta_x = data->ray.x - data->player.x;
	const double	delta_y = data->ray.y - data->player.y;

	return (delta_x * data->player.direction_cos
		+ delta_y * data->player.direction_sin);
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
		while (!is_wall(data, y, x))
		{
			calculate_next_grid_distance(data, &y, &x);
			if (data->minimap_toggle && data->ray_toggle)
				fill_image_buffer(data->minimap, data->minimap.half_height
					+ (int)((data->ray.y - data->player.y)
						* data->value.scaled_grid_size),
					data->minimap.half_width
					+ (int)((data->ray.x - data->player.x)
						* data->value.scaled_grid_size), COLOR_RAY);
		}
		if (data->minimap_toggle && !data->ray_toggle)
			draw_minimap_ray(data);
		draw_vertical_line(data, ray, get_perp_wall_dist(data));
		ray++;
	}
}
