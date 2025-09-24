/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/24 16:12:14 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Exit function for the parsing
void	exit_pars(char *err_msg, char *line, t_data *data)
{
	(void)data;
	if (data->fd > 0)
	{
		get_next_line(data->fd, true);
		close (data->fd);
	}
	if (line)
		free(line);
	exit_cub3d(err_msg);
}

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
		exit_pars("Malloc Error!", NULL, NULL);
	return (new_str);
}

// Converts and distributes element depending on what it is;
size_t	distribute_element(char *line, t_data *data, size_t filemask)
{
	size_t	flag;
	
	flag = 0;
	if (!ft_strncmp(line, "NO", 2) && !data->textures[NORTH].buffer)
		flag = get_image(NORTH, line, data);
	else if (!ft_strncmp(line, "EA", 2) && !data->textures[EAST].buffer)
		flag = get_image(EAST, line, data);
	else if (!ft_strncmp(line, "SO", 2) && !data->textures[SOUTH].buffer)
		flag = get_image(SOUTH, line, data);
	else if (!ft_strncmp(line, "WE", 2) && !data->textures[WEST].buffer)
		flag = get_image(WEST, line, data);
	else if (!ft_strncmp(line, "F", 1))
		flag = get_color(FLOOR, line, data);
	else if (!ft_strncmp(line, "C", 1))
		flag = get_color(CEILING, line, data);
	else if (line[0])
		exit_pars("Garbage!", line, data);
	if (flag & filemask)
		exit_pars("Multiple occurance of the same element!", line, data);
	return (flag);
}

// Handles the textures and colors from the .cub file
size_t	get_elements(t_data *data)
{
	char	*line;
	size_t	filemask;
	size_t	line_count;

	filemask = 0;
	line_count = 0;
	while (1)
	{
		line = get_next_line(data->fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", line, data);
		if (!line)
			break ;
		line = remove_first_spaces(line);
		filemask += distribute_element(line, data, filemask);
		free(line);
		line_count++;
		if (filemask == (1 << ELEMENT_COUNT) - 1)
			return (line_count);
	}
	if (filemask < (1 << ELEMENT_COUNT) - 1)
		exit_pars("Missing elements!", line, data);
	return (line_count);
}

void	parsing(int argc, char **argv, t_data *data)
{
	size_t	line_count;

	arg_validation(argc, argv[1]);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
		exit_pars("Failed to open file!", NULL, data);
	line_count = get_elements(data);
	line_count += get_map_size(data);
	close(data->fd);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
		exit_pars("Failed to open file!", NULL, data);
	get_map(line_count, data);
	close(data->fd);
	get_player(data->map.map, data);
}
