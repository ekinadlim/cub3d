/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:13:08 by eadlim            #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

// Checks if the line is valid according to the MAP_CHAR_SET macro
static void	is_valid_line(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->pars.line[i] && data->pars.line[i] != '\n')
	{
		while (MAP_CHAR_SET[j])
		{
			if (data->pars.line[i] == MAP_CHAR_SET[j])
			{
				get_player(i, data->map.height, MAP_CHAR_SET[j], data);
				break ;
			}
			j++;
		}
		if (!MAP_CHAR_SET[j])
			exit_pars("Invalid map!", data);
		j = 0;
		i++;
	}
	data->map.height++;
	if (data->map.width < (int)i)
		data->map.width = i;
}

// gets map size
void	get_map_size(t_data *data)
{
	bool	has_nl;

	has_nl = false;
	is_valid_line(data);
	free(data->pars.line);
	data->pars.line = NULL;
	while (1)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			break ;
		if (!ft_strncmp(data->pars.line, "\n", 2))
			has_nl = true;
		else if (has_nl)
			exit_pars("Map separated by new line(s)!", data);
		else
			is_valid_line(data);
		if (data->map.height > MAX_HEIGHT || data->map.width > MAX_WIDTH)
			exit_pars("Map too big!", data);
		free(data->pars.line);
		data->pars.line = NULL;
	}
}
