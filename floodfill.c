/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:26:24 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/20 19:21:58 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Check for open walls;
void	floodfill(size_t x, size_t y, char **map, t_data *data)
{
	for (size_t i = 0; i < (size_t)data->map.height; i++)
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
	usleep(100000);
	if (x == 0 || y == 0)
		exit_cub3d("We got contact with the void!");
	if (map[y + 1][x] == ' ' || map[y + 1][x] == '\0')
		exit_cub3d("We got contact with the void!");
	if (map[y - 1][x] == ' ' || map[y - 1][x] == '\0')
		exit_cub3d("We got contact with the void!");
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0')
		exit_cub3d("We got contact with the void!");
	if (map[y][x - 1] == ' ' || map[y][x - 1] == '\0')
		exit_cub3d("We got contact with the void!");
	
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
