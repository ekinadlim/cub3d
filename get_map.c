/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:27 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/11 17:43:30 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_map_size(int fd, t_data *data)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		while (line[i])
		{
			
		}
		
	}
	
}

void	get_map(int fd, t_data *data)
{
	get_map_size(fd, data);
}