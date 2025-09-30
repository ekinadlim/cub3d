/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:27 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 15:05:38 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*line_to_map(t_data *data)
{
	char	*map_line;
	int		i;

	i = 0;
	map_line = ft_calloc(data->map.width + 1, sizeof(char));
	if (!map_line)
		exit_pars("Malloc Error!", data);
	while (data->pars.line[i] && data->pars.line[i] != '\n')
	{
		map_line[i] = data->pars.line[i];
		i++;
	}
	while (data->map.width > i)
	{
		map_line[i] = ' ';
		i++;
	}
	return (map_line);
}

void	file_to_map(t_data *data)
{
	int	i;

	i = 0;
	data->map.map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.map)
		exit_pars("Malloc Error!", data);
	while (data->map.height > i)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			break ;
		data->map.map[i] = line_to_map(data);
		free(data->pars.line);
		data->pars.line = NULL;
		i++;
	}
}

void	get_map(size_t start, t_data *data)
{
	while (start)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			break ;
		free(data->pars.line);
		data->pars.line = NULL;
		start--;
	}
	file_to_map(data);
}
