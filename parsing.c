/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/02 15:44:57 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* size_t	count_file_lines(int fd)
{
	char	*line;
	size_t	count;

	line = get_next_line(fd);
	if (ft_errno(false))
		exit_cub3d("GNL: Malloc Error!");
	if (ft_strncmp(line, "\n", 2))
		count = 0;
	else
		count = 1;
	while (line)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
	}
	return 0;
}

char	**get_file_content(char *path)
{
	int		fd;
	char	*line;
	char	**content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_cub3d("Failed to open file!");
	line = get_next_line(fd);
	if (ft_errno(false))
		exit_cub3d("GNL: Malloc Error!");
	while (line)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
	}
	return NULL;
} */

/* // Directions: NO=North; EA=East; SO=South; WE=West
void	*get_texture(char *path, char *direction)
{
	void	*texture;
	char	**content;

	content = get_file_content(path);
	return (texture);
} */

void	parsing(int argc, char **argv, t_data *data)
{
	(void)data;
	arg_validation(argc, argv[1]);
/* 	data->texture.north = get_texture(argv[1], "NO");
	data->texture.east = get_texture(argv[1], "EA");
	data->texture.south = get_texture(argv[1], "SO");
	data->texture.west = get_texture(argv[1], "WE"); */
}
