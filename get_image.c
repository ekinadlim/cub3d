/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:02:58 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/20 15:03:31 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
