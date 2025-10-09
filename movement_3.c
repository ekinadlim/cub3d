/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:33:41 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:33:42 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static bool	validate_x_position(t_data *data, double x)
{
	if (data->player.y - (int)data->player.y > 0.8001)
	{
		if (is_wall(data, data->player.y + 1, x))
			return (false);
	}
	else if (data->player.y - (int)data->player.y < 0.1999)
	{
		if (is_wall(data, data->player.y - 1, x))
			return (false);
	}
	if (is_wall(data, data->player.y, x))
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
	bool	can_move;

	can_move = false;
	if (fabs(x) < EPSILON)
		return ;
	if (x > 0)
		ccd_positive_x(data, &x, 0.2);
	else if (x < 0)
		ccd_negative_x(data, &x, -0.2);
	if (fabs(x) < EPSILON)
		return ;
	data->player.x += x;
	data->render_required = true;
}
