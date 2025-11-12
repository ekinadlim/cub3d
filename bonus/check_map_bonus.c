/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:43:38 by eadlim            #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

static bool	has_surroundable(t_vec_2d_int pos, char **map, t_data *data)
{
	if (pos.y == data->map.height - 1 || pos.y == 0 || pos.x == data->map.width
		|| pos.x == 0)
		return (false);
	if (map[pos.y + 1][pos.x] != '0' && map[pos.y + 1][pos.x] != '1'
		&& map[pos.y + 1][pos.x] != 'D')
		return (false);
	if (map[pos.y - 1][pos.x] != '0' && map[pos.y - 1][pos.x] != '1'
		&& map[pos.y - 1][pos.x] != 'D')
		return (false);
	if (map[pos.y][pos.x + 1] != '0' && map[pos.y][pos.x + 1] != '1'
		&& map[pos.y][pos.x + 1] != 'D')
		return (false);
	if (map[pos.y][pos.x - 1] != '0' && map[pos.y][pos.x - 1] != '1'
		&& map[pos.y][pos.x - 1] != 'D')
		return (false);
	return (true);
}

void	check_map(char **map, t_data *data)
{
	t_vec_2d_int	pos;

	pos = (t_vec_2d_int){0, 0};
	while (pos.y < data->map.height)
	{
		while (pos.x < data->map.width)
		{
			if ((map[pos.y][pos.x] == '0' || map[pos.y][pos.x] == 'D')
				&& !has_surroundable(pos, map, data))
				exit_pars("Map is not surrounded by walls!", data);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
}
