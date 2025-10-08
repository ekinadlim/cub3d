/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:10:03 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 14:10:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	update_y_coordinate_and_wall_hit(t_data *data, int *y)
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

static void	update_x_coordinate_and_wall_hit(t_data *data, int *x)
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

static void	move_ray(t_data *data, int *y, int *x)
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

void	calculate_next_grid_distance(t_data *data, int *y, int *x)
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
