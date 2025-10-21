/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:33 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:33:34 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static bool	validate_y_position(t_data *data, double y)
{
	if (data->player.x - (int)data->player.x > 0.8001)
	{
		if (is_wall(data, y, data->player.x + 1)
			&& !is_closed_door(data, y, data->player.x + 1))
			return (false);
	}
	else if (data->player.x - (int)data->player.x < 0.1999)
	{
		if (is_wall(data, y, data->player.x - 1)
			&& !is_closed_door(data, y, data->player.x - 1))
			return (false);
	}
	if (is_wall(data, y, data->player.x)
		&& !is_closed_door(data, y, data->player.x))
		return (false);
	return (true);
}

static void	y_doors(t_data *data, double y,
	char door, bool (*is_door)(const t_data *, double, double))
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

static void	ccd_positive_y(t_data *data, double *y, double offset)
{
	int	i;

	i = 1;
	while (i < *y)
	{
		if (!validate_y_position(data, data->player.y + i))
		{
			*y = (int)data->player.y + i - data->player.y - offset;
			return ;
		}
		i++;
	}
	if (!validate_y_position(data, data->player.y + *y + offset))
		*y = (int)data->player.y + i - data->player.y - offset;
}

static void	ccd_negative_y(t_data *data, double *y, double offset)
{
	int	i;

	i = -1;
	while (i > *y)
	{
		if (!validate_y_position(data, data->player.y + i))
		{
			*y = (int)data->player.y + i + 1 - data->player.y - offset;
			return ;
		}
		i--;
	}
	if (!validate_y_position(data, data->player.y + *y + offset))
		*y = (int)data->player.y + i + 1 - data->player.y - offset;
}

void	move_y(t_data *data, double y)
{
	if (fabs(y) < EPSILON)
		return ;
	y_doors(data, data->player.y, 'D', is_open_door);
	if (y > 0)
		ccd_positive_y(data, &y, 0.2);
	else if (y < 0)
		ccd_negative_y(data, &y, -0.2);
	y_doors(data, data->player.y + y, 'd', is_closed_door);
	if (fabs(y) < EPSILON)
		return ;
	data->player.y += y;
	data->render_required = true;
}
