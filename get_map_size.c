/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:13:08 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/09 18:15:43 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

// Returns the starting line
static size_t	skip_first_newlines(t_data *data)
{
	size_t	start;

	start = 0;
	while (1)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			exit_pars("Map missing!", data);
		if (ft_strncmp(data->pars.line, "\n", 2))
		{
			is_valid_line(data);
			if (data->map.height > MAX_HEIGHT || data->map.width > MAX_WIDTH)
				exit_pars("Map too big!", data);
			free(data->pars.line);
			data->pars.line = NULL;
			return (start);
		}
		start++;
		free(data->pars.line);
		data->pars.line = NULL;
	}
	return (start);
}

// Returns the starting line of the map
size_t	get_map_size(t_data *data)
{
	size_t	start;
	bool	has_nl;

	has_nl = false;
	start = skip_first_newlines(data);
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
	return (start);
}
