/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:27 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/24 16:19:33 by eadlim           ###   ########.fr       */
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
		exit_pars("Malloc Error!", file_line, data);
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

void	file_to_map(char *line, t_data *data)
{
	int	i;
	
	i = 0;
	data->map.map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.map)
		exit_pars("Malloc Error!", line, data);
	while (data->map.height > i)
	{
		line = get_next_line(data->fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", line, data);
		if (!line)
			break ;
		data->map.map[i] = line_to_map(line, data);
		free(line);
		i++;
	}
}

void	get_map(size_t start, t_data *data)
{
	char	*line;
	
	while (start)
	{
		line = get_next_line(data->fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", line, data);
		if (!line)
			break ;
		free(line);
		start--;
	}
	file_to_map(line, data);
}
