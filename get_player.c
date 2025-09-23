/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:25:23 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/23 14:03:14 by eadlim           ###   ########.fr       */
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

// Check for open walls;
void	floodfill(int x, int y, char **map, t_data *data)
{
	/* 	for (size_t i = 0; i < (size_t)data->map.height; i++)
		{
			for (size_t j = 0; j < (size_t)data->map.width; j++)
			{
				if (j == x && i == y)
					printf("P");
				else
					printf("%c", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		usleep(100000); */
	if (x == 0 || y == 0)
		exit_pars("We got contact with the void!", NULL, data);
	if (map[y + 1][x] == ' ' || map[y + 1][x] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[y - 1][x] == ' ' || map[y - 1][x] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[y][x - 1] == ' ' || map[y][x - 1] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	map[y][x] = 'X';
	if (map[y + 1][x] == '0')
		floodfill(x, y + 1, map, data);
	if (map[y - 1][x] == '0')
		floodfill(x, y - 1, map, data);
	if (map[y][x + 1] == '0')
		floodfill(x + 1, y, map, data);
	if (map[y][x - 1] == '0')
		floodfill(x - 1, y, map, data);
}

void	get_pos_and_dir(size_t x, size_t y, char c, t_data *data)
{
	if (data->player.x || data->player.y)
		exit_pars("Only one player allowed!", NULL, data);
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
		exit_pars("No idea how this happened!", NULL, data);
}

// save player coordinates (x + 0.5, y + 0.5);
// save player directions (E=0, S=90, W=180, N=270)
void	get_player(char **map, t_data *data)
{
	t_vec_2d_size_t	i;
	t_vec_2d_int	player;

	i = (t_vec_2d_size_t){0, 0};
	player = (t_vec_2d_int){-1, -1};
	while (map[i.y])
	{
		while (map[i.y][i.x])
		{
			if (map[i.y][i.x] == 'E' || map[i.y][i.x] == 'S'
				|| map[i.y][i.x] == 'W' || map[i.y][i.x] == 'N')
			{
				get_pos_and_dir(i.x, i.y, map[i.y][i.x], data);
				player.x = i.x;
				player.y = i.y;
			}
			i.x++;
		}
		i.y++;
		i.x = 0;
	}
	if (player.x < 0 || player.y < 0)
		exit_pars("Player is missing!", NULL, data);
	floodfill(player.x, player.y, map, data);
	clean_up_map(map);
}
