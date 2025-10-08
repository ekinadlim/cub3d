/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:29 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:33:30 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	move_forward(t_data *data) //data->player.direction_sin??????
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

void	move_backwards(t_data *data)
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
