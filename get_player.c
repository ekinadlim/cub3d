/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:25:23 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/20 18:53:06 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_pos_and_dir(size_t x, size_t y, char c, t_data *data)
{
	if (data->player.x || data->player.y)
		exit_cub3d("Only one player allowed!");
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
	if (c == 'E')
		data->player.direction = 0;
	else if (c == 'S')
		data->player.direction = 90;
	else if (c == 'W')
		data->player.direction = 180;
	else if (c == 'N')
		data->player.direction = 270;
	else
		exit_cub3d("No idea how this happened!");
}

// save player coordinates (x + 0.5, y + 0.5);
// save player directions (E=0, S=90, W=180, N=270) 
void	get_player(char **map, t_data *data)
{
	size_t	x;
	size_t	y;
	size_t	player_x;
	size_t	player_y;
	
	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (ft_isalpha(map[y][x]))
			{
				get_pos_and_dir(x, y, map[y][x], data);
				player_x = x;
				player_y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
	floodfill(player_x, player_y, map, data);
}
