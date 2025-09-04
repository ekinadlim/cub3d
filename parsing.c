/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/04 18:43:21 by eadlim           ###   ########.fr       */
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
		else if (str[i] == '\v')
			exit_cub3d("Vertical Tab not allowed!");
		else if (str[i] == '\f')
			exit_cub3d("Form feed not allowed!");
		else if (str[i] == '\r')
			exit_cub3d("Carriage return (not allowed!");
		i++;
	}
}

void	get_image(t_image *img, t_data *data, char *file)
{
	size_t	len;

	len = ft_strlen(file) - 1;
	file[len] = '\0';
	img->buffer = mlx_xpm_file_to_image(data->mlx, file, &img->width,
			&img->height);
	if (!img->buffer)
		exit_cub3d("MLX: Failed to convert xpm to img!");
	img->address = mlx_get_data_addr(img->buffer, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	if (!img->address)
		exit_cub3d("MLX: Failed to get data address!");
}

size_t	get_color(t_data *data, char **element)
{
	int		color;
	size_t	i;

	i = 1;
	while (element[i])
	{
		
	}
	
}

// Converts and distributes element depending on what it is;
// Do this with bitwise operators if there is time later on
// using the e_cardinal_directions and << operator like "return (1 << NORTH)"
size_t	distribute_element(char **element, t_data *data)
{
	if (!ft_strncmp(element[0], "NO", 3))
		return (get_image(&data->texture[NORTH], data, element[1]), free_2d_array(element), fm_north);
	if (!ft_strncmp(element[0], "EA", 3))
		return (get_image(&data->texture[EAST], data, element[1]), free_2d_array(element), fm_east);
	if (!ft_strncmp(element[0], "SO", 3))
		return (get_image(&data->texture[SOUTH], data, element[1]), free_2d_array(element), fm_south);
	if (!ft_strncmp(element[0], "WE", 3))
		return (get_image(&data->texture[WEST], data, element[1]), free_2d_array(element), fm_west);
	if (!ft_strncmp(element[0], "F", 2))
		return (get_color(data, element));
	if (!ft_strncmp(element[0], "C", 3))
		return (get_color(data, element));
	free_2d_array(element);
	return (0);
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
	ft_printf("NO: %s\nEA: %s\nSO: %s\nWE: %s\n", data->texture[NORTH],
		data->texture[EAST], data->texture[SOUTH], data->texture[WEST]);
}
