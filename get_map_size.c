/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:13:08 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/17 15:13:29 by eadlim           ###   ########.fr       */
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
			exit_cub3d("Invalid map!");
		j = 0;
		i++;
	}
	data->map.height++;
	if (data->map.width < (int)i)
		data->map.width = i;
}

// Returns the starting line
size_t	skip_first_newlines(int fd, t_data *data)
{
	size_t	start;
	char	*line;

	start = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			exit_cub3d("Map missing!");
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
size_t	get_map_size(int fd, t_data *data)
{
	char	*line;
	size_t	start;
	bool	has_nl;

	has_nl = false;
	start = skip_first_newlines(fd, data);
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 2))
		{
			free(line);
			if (!has_nl)
				has_nl = true;
			continue ;
		}
		if (has_nl)
		{
			free(line);
			exit_cub3d("Map separated by new line(s)!");
		}
		is_valid_line(line, data);
		free(line);
	}
	return (start);
}
