/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:43:38 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/24 15:14:39 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	has_surroundable(t_vec_2d_int pos, char **map, t_data *data)
{
	size_t	i;

	i = 0;
	if (pos.y == data->map.height || pos.y == 0 || pos.x == data->map.width
		|| pos.x == 0)
		return (false);
	if (map[pos.y + 1][pos.x] != '0' && map[pos.y + 1][pos.x] != '1')
		return (false);
	if (map[pos.y - 1][pos.x] != '0' && map[pos.y - 1][pos.x] != '1')
		return (false);
	if (map[pos.y][pos.x + 1] != '0' && map[pos.y][pos.x + 1] != '1')
		return (false);
	if (map[pos.y][pos.x - 1] != '0' && map[pos.y][pos.x - 1] != '1')
		return (false);
	return (true);
}

void	check_map(t_vec_2d_int player_pos, char **map, t_data *data)
{
	t_vec_2d_int	pos;

	pos = (t_vec_2d_int){0, 0};
	(void)player_pos;
	while (pos.y < data->map.height)
	{
		while (pos.x < data->map.width)
		{
			if (map[pos.y][pos.x] == '0' && !has_surroundable(pos, map, data))
				exit_pars("Map is not surrounded by walls!", NULL, data);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
}

// Check for open walls;
void	floodfill(t_vec_2d_int pos, char **map, t_data *data)
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
	if (pos.x == 0 || pos.y == 0)
		exit_pars("We got contact with the void!", NULL, data);
	if (map[pos.y + 1][pos.x] == ' ' || map[pos.y + 1][pos.x] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[pos.y - 1][pos.x] == ' ' || map[pos.y - 1][pos.x] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[pos.y][pos.x + 1] == ' ' || map[pos.y][pos.x + 1] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	if (map[pos.y][pos.x - 1] == ' ' || map[pos.y][pos.x - 1] == '\0')
		exit_pars("We got contact with the void!", NULL, data);
	map[pos.y][pos.x] = 'X';
	if (map[pos.y + 1][pos.x] == '0')
		floodfill((t_vec_2d_int){pos.x, pos.y + 1}, map, data);
	if (map[pos.y - 1][pos.x] == '0')
		floodfill((t_vec_2d_int){pos.x, pos.y - 1}, map, data);
	if (map[pos.y][pos.x + 1] == '0')
		floodfill((t_vec_2d_int){pos.x + 1, pos.y}, map, data);
	if (map[pos.y][pos.x - 1] == '0')
		floodfill((t_vec_2d_int){pos.x - 1, pos.y}, map, data);
}
