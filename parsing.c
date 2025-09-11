/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/11 17:26:01 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Removes all spaces in the beginning of str
// but exits if there are other whitespaces through out the rest of str 
char	*allow_only_normal_spaces(char *str)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	new_str = ft_substr(str, i, ft_strlen(str) - i - 1);
	free(str);
	if (!new_str)
		exit_cub3d("Malloc Error!");
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '\t')
			return (free(new_str), exit_cub3d("Horizonal Tab not allowed!"), NULL);
		if (new_str[i] == '\v')
			return (free(new_str), exit_cub3d("Vertical Tab not allowed!"), NULL);
		if (new_str[i] == '\f')
			return (free(new_str), exit_cub3d("Form feed not allowed!"), NULL);
		if (new_str[i] == '\r')
			return (free(new_str), exit_cub3d("Carriage return not allowed!"), NULL);
		i++;
	}
	return (new_str);
}

// Retrieves the image from the xpm file and returns a mask depending on the direction
int	get_image(t_data *data, char *line, int direction)
{
	char	*path;
	
	path = ft_substr(line, 3, ft_strlen(line) - 1);
	free(line);
	if (!path)
		exit_cub3d("Substr: Malloc Error!");
	data->textures[direction].buffer = mlx_xpm_file_to_image(data->mlx, path, &data->textures[direction].width, &data->textures[direction].height);
	if (!data->textures[direction].buffer)
		exit_cub3d("MLX: Failed to convert xpm to img!");
	data->textures[direction].address = mlx_get_data_addr(data->textures[direction].buffer, &data->textures[direction].bits_per_pixel,
			&data->textures[direction].size_line, &data->textures[direction].endian);
	if (!data->textures[direction].address)
		exit_cub3d("MLX: Failed to get data address!");
	return (1 << direction);
}

int	get_color_number(char *element, size_t *i)
{
	char	str_num[5];
	size_t	digit;

	digit = 0;
	ft_bzero(str_num, 5);
	while (element[*i])
	{
		if (element[*i] >= '0' && element[*i] <= '9')
		{
			if (str_num[0] && element[*i] == ' ')
				exit_cub3d("Invalid Color Code!");
			str_num[digit++] = element[*i];
		}
		else if (element[*i] == ',')
		{
			if (!str_num[0])
				exit_cub3d("Missing number for color code!");
			(*i)++;
			return (ft_atoi(str_num));
		}
		else if (element[*i] != ' ')
			exit_cub3d("Garbage in Surface element!");
		(*i)++;
	}
	return (ft_atoi(str_num));
}

size_t	get_color(t_data *data, char *element, int surface)
{
	int		color_code;
	int		one_color;
	int		color_shift;
	size_t	i;
	
	color_shift = 2;
	color_code = 0;
	i = 2;
	while (element[i])
	{
		one_color = get_color_number(&(*element), &i);
		if (one_color == -1)
		{
			if (color_shift != 0)
				exit_cub3d("Not right amount of colors!");
		}
		color_code += one_color << (8 * color_shift);
		color_shift--;
		
	}
	data->surface[surface] = color_code;
	return (1 << (surface + 4));
}

// Converts and distributes element depending on what it is;
size_t	distribute_element(char *line, t_data *data, size_t filemask)
{
	size_t	flag;
	
	flag = 0;
	if (!ft_strncmp(line, "NO ", 3))
		flag = get_image(data, line, NORTH);
	else if (!ft_strncmp(line, "EA ", 3))
		flag = get_image(data, line, EAST);
	else if (!ft_strncmp(line, "SO ", 3))
		flag = get_image(data, line, SOUTH);
	else if (!ft_strncmp(line, "WE ", 3))
		flag = get_image(data, line, WEST);
	else if (!ft_strncmp(line, "F ", 2))
		flag = get_color(data, line, FLOOR);
	else if (!ft_strncmp(line, "C ", 2))
		flag = get_color(data, line, CEILING);
/* 	else if (line[0])
		exit_cub3d("Garbage elements in the file!"); */
	if (flag & filemask)
		exit_cub3d("Multiple occurance of the same element!");
	return (flag);
}

// Handles the textures and colors from the .cub file
void	get_elements(int fd, t_data *data)
{
	char	*line;
	size_t	filemask;

	filemask = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (ft_errno(false))
			exit_cub3d("GNL: Malloc Error!");
		if (!line)
			break ;
		line = allow_only_normal_spaces(line);
		filemask += distribute_element(line, data, filemask);
	}
	if (filemask < (1 << ELEMENT_COUNT) - 1)
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
	get_map(fd, data);
}
