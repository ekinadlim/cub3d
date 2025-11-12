/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:25:23 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 19:41:49 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_player(int pos_x, int pos_y, char c, t_data *data)
{
	if (c == 'D' && !(data->filemask & 1 << (DOOR + 2)))
		exit_pars("Missing Door Texture", data);
	if (c == 'E')
		data->player.direction = 0;
	else if (c == 'S')
		data->player.direction = 90;
	else if (c == 'W')
		data->player.direction = 180;
	else if (c == 'N')
		data->player.direction = 270;
	else
		return ;
	if (data->player.x || data->player.y)
		exit_pars("Only one player allowed!", data);
	data->player.x = pos_x + 0.5;
	data->player.y = pos_y + 0.5;
	data->player.direction_in_radians
		= data->player.direction * PI_180;
}
