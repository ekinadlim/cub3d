/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/02 16:55:53 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Skip the lines that you dont need and store the ones you do need in data
t_texture	get_texture(int fd, t_data *data)
{
	t_texture	texture;
	char		*line;
	int			fd;
	int			count;
	
	while (line)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
	}
	return (texture);
}

void	parsing(int argc, char **argv, t_data *data)
{
	int	fd;
	
	arg_validation(argc, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_cub3d("Failed to open file!");
	data->texture = get_texture(fd, data);
}
