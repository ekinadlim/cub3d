/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:27 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/17 15:13:25 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*line_to_map(char *file_line, t_data *data)
{
	char	*map_line;
	int		i;
	
	i = 0;
	map_line = ft_calloc(data->map.width + 1, sizeof(char));
	if (!map_line)
		exit_cub3d("Malloc Error!");
	while (file_line[i] && file_line[i] != '\n')
	{
		map_line[i] = file_line[i];
		i++;
	}
	while (data->map.width > i)
	{
		map_line[i] = ' ';
		i++;
	}
	return (map_line);
}

void	file_to_map(int fd, char *line, t_data *data)
{
	int	i;
	
	i = 0;
	data->map.map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.map)
		exit_cub3d("Malloc Error!");
	while (data->map.height > i)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		data->map.map[i] = line_to_map(line, data);
		free(line);
		i++;
	}
}

void	get_map(int fd, size_t start, t_data *data)
{
	char	*line;
	
	while (start)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		free(line);
		start--;
	}
	file_to_map(fd, line, data);
}
