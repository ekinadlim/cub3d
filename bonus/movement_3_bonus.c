/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:41 by apartowi          #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

static bool	validate_x_position(t_data *data, double x)
{
	if (data->player.y - (int)data->player.y > 0.8001)
	{
		if (is_wall(data, data->player.y + 1, x)
			&& !is_closed_door(data, data->player.y + 1, x))
			return (false);
	}
	else if (data->player.y - (int)data->player.y < 0.1999)
	{
		if (is_wall(data, data->player.y - 1, x)
			&& !is_closed_door(data, data->player.y - 1, x))
			return (false);
	}
	if (is_wall(data, data->player.y, x)
		&& !is_closed_door(data, data->player.y, x))
		return (false);
	return (true);
}

static void	ccd_positive_x(t_data *data, double *x, double offset)
{
	int	i;

	i = 1;
	while (i < *x)
	{
		if (!validate_x_position(data, data->player.x + i))
		{
			*x = (int)data->player.x + i - data->player.x - offset;
			return ;
		}
		i++;
	}
	if (!validate_x_position(data, data->player.x + *x + offset))
		*x = (int)data->player.x + i - data->player.x - offset;
}

static void	ccd_negative_x(t_data *data, double *x, double offset)
{
	int	i;

	i = -1;
	while (i > *x)
	{
		if (!validate_x_position(data, data->player.x + i))
		{
			*x = (int)data->player.x + i + 1 - data->player.x - offset;
			return ;
		}
		i--;
	}
	if (!validate_x_position(data, data->player.x + *x + offset))
		*x = (int)data->player.x + i + 1 - data->player.x - offset;
}

void	move_x(t_data *data, double x)
{
	if (fabs(x) < EPSILON)
		return ;
	x_doors(data, data->player.x, 'D', is_open_door);
	if (x > 0)
		ccd_positive_x(data, &x, 0.2);
	else if (x < 0)
		ccd_negative_x(data, &x, -0.2);
	x_doors(data, data->player.x + x, 'd', is_closed_door);
	if (fabs(x) < EPSILON)
		return ;
	data->player.x += x;
}
