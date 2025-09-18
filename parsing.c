/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/18 18:05:06 by eadlim           ###   ########.fr       */
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

char	*get_path(char *line)
{
	size_t	start;
	size_t	len;
	size_t	i;
	char	*path;
	
	i = 2;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (i == 2 || !line[i])
		return (free(line), exit_cub3d("Wrong Texture Format!"), NULL);
	start = i;
	while (line[i] && !is_whitespace(line[i]))
		i++;
	len = i - start;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			return (free(line), exit_cub3d("Wrong Texture Format!"), NULL);
	}
	path = ft_substr(line, start, len);
	if (!path)
		return (free(line), exit_cub3d("Substr: Malloc Error!"), NULL);
	return (free(line), path);
}

// Retrieves the image from the xpm file and returns a mask depending on the direction
int	get_image(t_data *data, char *line, int direction)
{
	char	*path;
	
	path = get_path(line);
	data->textures[direction].buffer = mlx_xpm_file_to_image(data->mlx, path, &data->textures[direction].width, &data->textures[direction].height);
	printf("%s\n", path);
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
	while (element[*i] && element[*i] != '\n')
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

size_t	get_color(t_data *data, char *line, int surface)
{
	int		color_code;
	int		one_color;
	int		color_shift;
	size_t	i;
	
	color_shift = 2;
	color_code = 0;
	i = 1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (i == 1 || (line[i] && line[i] == '\n'))
	{
		free(line);
		exit_cub3d("Wrong Surface Format");
	}
	while (line[i])
	{
		one_color = get_color_number(&(*line), &i);
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
}
