/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/03 16:04:54 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Removes all spaces in the beginning of str
// but exits if there are other whitespaces through out the rest of str
static char	*remove_first_spaces(char *str, t_data *data)
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
		exit_pars("Malloc Error!", data);
	return (new_str);
}

// Converts and distributes element depending on what it is;
static int	distribute_element(t_data *data, int filemask)
{
	int	flag;

	flag = 0;
	data->pars.line = remove_first_spaces(data->pars.line, data);
	if (!ft_strncmp(data->pars.line, "NO", 2))
		flag = get_image(NORTH, filemask, data);
	else if (!ft_strncmp(data->pars.line, "EA", 2))
		flag = get_image(EAST, filemask, data);
	else if (!ft_strncmp(data->pars.line, "SO", 2))
		flag = get_image(SOUTH, filemask, data);
	else if (!ft_strncmp(data->pars.line, "WE", 2))
		flag = get_image(WEST, filemask, data);
	else if (!ft_strncmp(data->pars.line, "F", 1))
		flag = get_color(FLOOR, filemask, data);
	else if (!ft_strncmp(data->pars.line, "C", 1))
		flag = get_color(CEILING, filemask, data);
	else if (data->pars.line[0])
		return (-(filemask + 1));
	return (flag);
}

// Handles the textures and colors from the .cub file
static size_t	get_elements(t_data *data)
{
	int		filemask;
	size_t	line_count;

	filemask = 0;
	line_count = 0;
	while (1)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			break ;
		filemask += distribute_element(data, filemask);
		if (data->pars.line)
			free(data->pars.line);
		data->pars.line = NULL;
		if (filemask < 0)
			exit_pars("Missing elements or Garbage in file!", data);
		line_count++;
		if (filemask == (1 << ELEMENT_COUNT) - 1)
			return (line_count);
	}
	return (line_count);
}

void	parsing(int argc, char **argv, t_data *data)
{
	size_t	line_count;

	arg_validation(argc, argv[1]);
	data->pars.fd = open(argv[1], O_RDONLY);
	if (data->pars.fd < 0)
		exit_pars("Failed to open file!", data);
	line_count = get_elements(data);
	line_count += get_map_size(data);
	close(data->pars.fd);
	data->pars.fd = open(argv[1], O_RDONLY);
	if (data->pars.fd < 0)
		exit_pars("Failed to open file!", data);
	get_map(line_count, data);
	get_player(data->map.map, data);
	close(data->pars.fd);
}
