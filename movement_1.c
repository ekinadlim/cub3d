/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:29 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/09 17:28:35 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	move_forward(t_data *data)
{
	double	y;
	double	x;

	y = sin(data->player.direction_in_radians)
		* (MOVEMENT_SPEED * data->delta_time);
	x = cos(data->player.direction_in_radians)
		* (MOVEMENT_SPEED * data->delta_time);
	move_y(data, y);
	move_x(data, x);
}

void	move_back(t_data *data)
{
	double	y;
	double	x;

	y = sin(data->player.direction_in_radians)
		* (-MOVEMENT_SPEED * data->delta_time);
	x = cos(data->player.direction_in_radians)
		* (-MOVEMENT_SPEED * data->delta_time);
	move_y(data, y);
	move_x(data, x);
}

void	move_left(t_data *data)
{
	double	y;
	double	x;

	y = sin(data->player.direction_in_radians - M_PI_2)
		* (MOVEMENT_SPEED * data->delta_time);
	x = cos(data->player.direction_in_radians - M_PI_2)
		* (MOVEMENT_SPEED * data->delta_time);
	move_y(data, y);
	move_x(data, x);
}

void	move_right(t_data *data)
{
	double	y;
	double	x;

	y = sin(data->player.direction_in_radians + M_PI_2)
		* (MOVEMENT_SPEED * data->delta_time);
	x = cos(data->player.direction_in_radians + M_PI_2)
		* (MOVEMENT_SPEED * data->delta_time);
	move_y(data, y);
	move_x(data, x);
}
