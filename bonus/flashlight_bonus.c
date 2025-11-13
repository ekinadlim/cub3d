/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:40:42 by apartowi          #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

static void	choose_darkness_level(t_data *data,
	const int y, const int x, const int radius)
{
	const int	distance
		= sqrt((x - data->image.half_width) * (x - data->image.half_width)
			+ (y - data->image.half_height) * (y - data->image.half_height));

	if (distance > 3 * radius)
		data->flashlight[y][x] = 35;
	else if (distance > 2.3 * radius)
		data->flashlight[y][x] = 3 + (distance - 2.3 * radius) / 4;
	else if (distance > 1.5 * radius)
		data->flashlight[y][x] = 1.2 + (distance - 1.5 * radius) / 32;
	else if (distance > 0.5 * radius)
		data->flashlight[y][x] = 1 + (distance - 0.5 * radius) / 512;
	else if (distance > 0.4 * radius)
		data->flashlight[y][x] = 1.1 - (distance - 0.4 * radius) / 128;
	else
		data->flashlight[y][x] = 1.1;
}

void	init_flashlight(t_data *data)
{
	const int	radius = WINDOW_HEIGHT / 8;
	int			y;
	int			x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			choose_darkness_level(data, y, x, radius);
			x++;
		}
		y++;
	}
}
