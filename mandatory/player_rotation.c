/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:47 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:33:48 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	turn_left(t_data *data, double speed)
{
	data->player.direction -= speed;
	data->render_required = true;
	if (data->player.direction < 0)
		data->player.direction += 360;
	data->player.direction_in_radians
		= data->player.direction * PI_180;
}

void	turn_right(t_data *data, double speed)
{
	data->player.direction += speed;
	data->render_required = true;
	if (data->player.direction > 360)
		data->player.direction -= 360;
	data->player.direction_in_radians
		= data->player.direction * PI_180;
}
