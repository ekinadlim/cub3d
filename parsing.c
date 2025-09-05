/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/05 18:09:19 by eadlim           ###   ########.fr       */
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
	t_image	*img;
	char	*path;
	
	path = ft_substr(line, 3, ft_strlen(line) - 1);
	free(line);
	if (!path)
		exit_cub3d("Substr: Malloc Error!");
	ft_printf("%s\n", path);
	img = &data->texture[direction];
	img->buffer = mlx_xpm_file_to_image(data->mlx, path, &img->width,
			&img->height);
	if (!img->buffer)
		exit_cub3d("MLX: Failed to convert xpm to img!");
	img->address = mlx_get_data_addr(img->buffer, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	if (!img->address)
		exit_cub3d("MLX: Failed to get data address!");
	return (1 << direction);
}

size_t	get_color(t_data *data, char *element, int surface)
{
	size_t	i;
	size_t	j;

	i = 3;
	j = 0;
	(void)data;
	while (element[i])
	{
		while (element[i])
		{
			if (element[i] < '0' || element[i] > '9' || element[i] != ',')
				exit_cub3d("Invlaid Floor or Ceiling data!");
			j++;
		}
		j = 0;
		i++;
	}
	return (1 << surface);
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
	else if (line[0])
		exit_cub3d("Garbage elements in the file!");
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
	ft_printf("NO: %s\nEA: %s\nSO: %s\nWE: %s\n", data->texture[NORTH],
		data->texture[EAST], data->texture[SOUTH], data->texture[WEST]);
}
