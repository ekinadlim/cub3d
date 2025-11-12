/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:25:36 by apartowi          #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

bool	is_closed_door(const t_data *data, const double y, const double x)
{
	if (y > 0 && y < data->map.height && x > 0 && x < data->map.width
		&& data->map.map[(int)y][(int)x] == 'D')
		return (true);
	return (false);
}

bool	is_open_door(const t_data *data, const double y, const double x)
{
	if (y > 0 && y < data->map.height && x > 0 && x < data->map.width
		&& data->map.map[(int)y][(int)x] == 'd')
		return (true);
	return (false);
}

void	y_doors(t_data *data, const double y,
	char door, bool (*is_door)(const t_data *, const double, const double))
{
	if (is_door(data, y - 1, data->player.x))
		data->map.map[(int)y - 1][(int)data->player.x] = door;
	if (is_door(data, y - 1, data->player.x - 1))
		data->map.map[(int)y - 1][(int)data->player.x - 1] = door;
	if (is_door(data, y - 1, data->player.x + 1))
		data->map.map[(int)y - 1][(int)data->player.x + 1] = door;
	if (is_door(data, y, data->player.x))
		data->map.map[(int)y][(int)data->player.x] = door;
	if (is_door(data, y, data->player.x - 1))
		data->map.map[(int)y][(int)data->player.x - 1] = door;
	if (is_door(data, y, data->player.x + 1))
		data->map.map[(int)y][(int)data->player.x + 1] = door;
	if (is_door(data, y + 1, data->player.x))
		data->map.map[(int)y + 1][(int)data->player.x] = door;
	if (is_door(data, y + 1, data->player.x - 1))
		data->map.map[(int)y + 1][(int)data->player.x - 1] = door;
	if (is_door(data, y + 1, data->player.x + 1))
		data->map.map[(int)y + 1][(int)data->player.x + 1] = door;
}

void	x_doors(t_data *data, const double x,
	char door, bool (*is_door)(const t_data *, const double, const double))
{
	if (is_door(data, data->player.y, x - 1))
		data->map.map[(int)data->player.y][(int)x - 1] = door;
	if (is_door(data, data->player.y - 1, x - 1))
		data->map.map[(int)data->player.y - 1][(int)x - 1] = door;
	if (is_door(data, data->player.y + 1, x - 1))
		data->map.map[(int)data->player.y + 1][(int)x - 1] = door;
	if (is_door(data, data->player.y, x))
		data->map.map[(int)data->player.y][(int)x] = door;
	if (is_door(data, data->player.y - 1, x))
		data->map.map[(int)data->player.y - 1][(int)x] = door;
	if (is_door(data, data->player.y + 1, x))
		data->map.map[(int)data->player.y + 1][(int)x] = door;
	if (is_door(data, data->player.y, x + 1))
		data->map.map[(int)data->player.y][(int)x + 1] = door;
	if (is_door(data, data->player.y - 1, x + 1))
		data->map.map[(int)data->player.y - 1][(int)x + 1] = door;
	if (is_door(data, data->player.y + 1, x + 1))
		data->map.map[(int)data->player.y + 1][(int)x + 1] = door;
}
