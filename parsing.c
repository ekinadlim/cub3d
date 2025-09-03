/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/03 17:00:17 by eadlim           ###   ########.fr       */
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

void	get_image(t_image *texture, void *mlx, char *file)
{
	texture->buffer = mlx_xpm_file_to_image(mlx, file, &texture->width, &texture->height);
	if (!texture->buffer)
		exit_cub3d("MLX: Failed to convert xpm to img!");
	texture->address = mlx_get_data_addr(texture->buffer, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->address)
		exit_cub3d("MLX: Failed to get data address!");
}

// Converts and distributes element depending on what it is
size_t	distribute_element(char **element, t_data *data)
{
	if (element[0] && element[1] && element[2])
		exit_cub3d("Element has too many arguments!"); // Dont forget to free split
	if (ft_strncmp(element[0], "NO", 3))
		get_image(&data->texture[NORTH], data->mlx, element[1]);
		
}

// Handles the textures and colors from the .cub file
void	get_elements(int fd, t_data *data)
{
	char	*line;
	char	**split;
	size_t	filemask;
	
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
		if (!split)
			exit_cub3d("Split: Malloc Error!");
		filemask += distribute_element(split, data);
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
	ft_printf("NO: %s\nEA: %s\nSO: %s\nWE: %s\n", data->texture[NORTH], data->texture[EAST], data->texture[SOUTH], data->texture[WEST]);
}
