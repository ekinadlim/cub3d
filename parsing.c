/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/20 18:27:44 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Removes all spaces in the beginning of str
// but exits if there are other whitespaces through out the rest of str 
char	*remove_first_spaces(char *str)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[len - 1] == '\n')
		len -= 1;
	new_str = ft_substr(str, i, len - i);
	free(str);
	if (!new_str)
		exit_cub3d("Malloc Error!");
	return (new_str);
}

// Converts and distributes element depending on what it is;
size_t	distribute_element(char *line, t_data *data, size_t filemask)
{
	size_t	flag;
	
	flag = 0;
	if (!ft_strncmp(line, "NO", 2))
		flag = get_image(data, line, NORTH);
	else if (!ft_strncmp(line, "EA", 2))
		flag = get_image(data, line, EAST);
	else if (!ft_strncmp(line, "SO", 2))
		flag = get_image(data, line, SOUTH);
	else if (!ft_strncmp(line, "WE", 2))
		flag = get_image(data, line, WEST);
	else if (!ft_strncmp(line, "F", 1))
		flag = get_color(data, line, FLOOR);
	else if (!ft_strncmp(line, "C", 1))
		flag = get_color(data, line, CEILING);
	else if (line[0])
		exit_cub3d("Garbage!");
	if (flag & filemask)
		exit_cub3d("Multiple occurance of the same element!");
	return (flag);
}

// Handles the textures and colors from the .cub file
size_t	get_elements(int fd, t_data *data)
{
	char	*line;
	size_t	filemask;
	size_t	line_count;

	filemask = 0;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		line = remove_first_spaces(line);
		filemask += distribute_element(line, data, filemask);
		line_count++;
		if (filemask == (1 << ELEMENT_COUNT) - 1)
			return (line_count);
	}
	if (filemask < (1 << ELEMENT_COUNT) - 1)
		exit_cub3d("Missing elements!");
	return (line_count);
}

void	parsing(int argc, char **argv, t_data *data)
{
	int		fd;
	size_t	line_count;

	arg_validation(argc, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_cub3d("Failed to open file!");
	line_count = get_elements(fd, data);
	line_count += get_map_size(fd, data);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_cub3d("Failed to open file!");
	get_map(fd, line_count, data);
	get_player(data->map.map, data);
}
