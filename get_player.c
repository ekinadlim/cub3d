/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:25:23 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 15:38:34 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	clean_up_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'X' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'N')
				map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
}

void	get_pos_and_dir(t_vec_2d_size_t pos, char c, t_data *data)
{
	if (data->player.x || data->player.y)
		exit_pars("Only one player allowed!", data);
	data->player.x = pos.x + 0.5;
	data->player.y = pos.y + 0.5;
	data->map.map[pos.y][pos.x] = '0';
	if (c == 'E')
		data->player.direction = 0;
	else if (c == 'S')
		data->player.direction = 90;
	else if (c == 'W')
		data->player.direction = 180;
	else if (c == 'N')
		data->player.direction = 270;
	else
		exit_pars("No idea how this happened!", data);
}

// save player coordinates (x + 0.5, y + 0.5);
// save player directions (E=0, S=90, W=180, N=270)
void	get_player(char **map, t_data *data)
{
	t_vec_2d_size_t	pos;
	t_vec_2d_int	player;

	pos = (t_vec_2d_size_t){0, 0};
	player = (t_vec_2d_int){-1, -1};
	while (map[pos.y])
	{
		while (map[pos.y][pos.x])
		{
			if (map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'S'
				|| map[pos.y][pos.x] == 'W' || map[pos.y][pos.x] == 'N')
			{
				get_pos_and_dir(pos, map[pos.y][pos.x], data);
				player.x = pos.x;
				player.y = pos.y;
			}
			pos.x++;
		}
		pos.y++;
		pos.x = 0;
	}
	if (player.x < 0 || player.y < 0)
		exit_pars("Player is missing!", data);
	clean_up_map(map);
	check_map(map, data);
}
