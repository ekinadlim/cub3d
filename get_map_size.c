/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:13:08 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/25 15:20:47 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Checks if the line is valid according to the MAP_CHAR_SET macro
void	is_valid_line(char *line, t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
	{
		while (MAP_CHAR_SET[j])
		{
			if (line[i] == MAP_CHAR_SET[j])
				break ;
			j++;
		}
		if (!MAP_CHAR_SET[j])
			exit_pars("Invalid map!", line, data);
		j = 0;
		i++;
	}
	data->map.height++;
	if (data->map.width < (int)i)
		data->map.width = i;
}

// Returns the starting line
size_t	skip_first_newlines(t_data *data)
{
	size_t	start;
	char	*line;

	start = 0;
	while (1)
	{
		line = get_next_line(data->fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", line, data);
		if (!line)
			exit_pars("Map missing!", line, data);
		if (ft_strncmp(line, "\n", 2))
		{
			is_valid_line(line, data);
			free(line);
			return (start);
		}
		start++;
		free(line);
	}
	return (start);
}

// Returns the starting line of the map
size_t	get_map_size(t_data *data)
{
	char	*line;
	size_t	start;
	bool	has_nl;

	has_nl = false;
	start = skip_first_newlines(data);
	while (1)
	{
		line = get_next_line(data->fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", line, data);
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 2))
			has_nl = true;
		else if (has_nl)
			exit_pars("Map separated by new line(s)!", line, data);
		else
			is_valid_line(line, data);
		free(line);
	}
	return (start);
}
