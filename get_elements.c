/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:28:38 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 18:33:52 by eadlim           ###   ########.fr       */
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

static bool	check_if_map_start(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->pars.line[i])
	{
		if (data->pars.line[i] != ' ' && data->pars.line[i] != '1' && data->pars.line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

// Converts and distributes element depending on what it is;
static int	distribute_element(t_data *data)
{
	int	flag;

	flag = 0;
	if (data->pars.line[0] && (data->pars.line[0] == ' ' || data->pars.line[0] == '1'))
	{
		if (check_if_map_start(data))
			return (-1);
	}
	data->pars.line = remove_first_spaces(data->pars.line, data);
	if (!ft_strncmp(data->pars.line, "DO", 2))
		return (get_images(DOOR, data) << COLOR_MASK_SKIP);
	if (!ft_strncmp(data->pars.line, "NO", 2))
		flag = get_images(NORTH, data);
	else if (!ft_strncmp(data->pars.line, "EA", 2))
		flag = get_images(EAST, data);
	else if (!ft_strncmp(data->pars.line, "SO", 2))
		flag = get_images(SOUTH, data);
	else if (!ft_strncmp(data->pars.line, "WE", 2))
		flag = get_images(WEST, data);
	else if (!ft_strncmp(data->pars.line, "F", 1))
		flag = get_color(FLOOR, data);
	else if (!ft_strncmp(data->pars.line, "C", 1))
		flag = get_color(CEILING, data);
	else if (data->pars.line[0])
		exit_pars("Missing elements or Garbage in file!", data);
	return (flag);
}

void	check_for_missing_elements(t_data *data)
{
	int	door_mask;

	door_mask = 0;
	if (data->filemask >= 1 << (DOOR + 2))
		door_mask = 1 << (DOOR + 2);
	if (!(data->filemask - door_mask == ((1 << ELEMENT_COUNT) - 1)))
		exit_pars("Missing elements!", data);
}

// Handles the textures and colors from the .cub file
size_t	get_elements(t_data *data)
{
	int		current_flag;
	size_t	line_count;

	line_count = 0;
	while (1)
	{
		data->pars.line = get_next_line(data->pars.fd, false);
		if (ft_errno(false))
			exit_pars("GNL: Malloc Error!", data);
		if (!data->pars.line)
			exit_pars("No map and maybe missing elements!", data);
		current_flag = distribute_element(data);
		if (current_flag == -1)
			break ;
		if (data->pars.line)
			free(data->pars.line);
		data->pars.line = NULL;
		data->filemask += current_flag;
		line_count++;
	}
	check_for_missing_elements(data);
	return (line_count);
}
