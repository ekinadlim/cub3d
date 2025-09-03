/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/03 16:17:14 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Exits if there are whitespaces expcept normal spaces
void	allow_only_normal_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			exit_cub3d("Horizonal Tab not allowed!");
		else if	(str[i] == '\v')
			exit_cub3d("Vertical Tab not allowed!");
		else if	(str[i] == '\f')
			exit_cub3d("Form feed not allowed!");
		else if	(str[i] == '\r')
			exit_cub3d("Carriage return not allowed!");
		i++;
	}
}

// Converts and distributes element depending on what it is
size_t	distribute_element(char **element, t_data *data)
{
	
}

// Handles the textures and colors from the .cub file
void	get_elements(int fd, t_data *data)
{
	char	*line;
	char	**split;
	size_t	filemask;
	size_t	current_mask_type;
	
	filemask = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		allow_only_normal_spaces(line);
		split = ft_split(line, ' ');
		free(line);
		if (ft_errno(false))
			exit_cub3d("Split: Malloc Error!");
		current_mask_type += distribute_element(split, data);
	}
	if (filemask < fm_complete)
		exit_cub3d("Missing elements!");
}

void	parsing(int argc, char **argv, t_data *data)
{
	int	fd;
	
	arg_validation(argc, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_cub3d("Failed to open file!");
	get_elements(fd, data);
	ft_printf("NO: %s\nEA: %s\nSO: %s\nWE: %s\n", data->texture.north, data->texture.east, data->texture.south, data->texture.west);
}
