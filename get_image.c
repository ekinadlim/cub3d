/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:02:58 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/24 16:11:31 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_path(char *line, t_data *data)
{
	size_t	start;
	size_t	len;
	size_t	i;
	char	*path;

	i = 2;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (i == 2 || !line[i])
		exit_pars("Wrong Texture Format!", line, data);
	start = i;
	while (line[i] && !is_whitespace(line[i]))
		i++;
	len = i - start;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			exit_pars("Wrong Texture Format!", line, data);
	}
	path = ft_substr(line, start, len);
	if (!path)
		exit_pars("Substr: Malloc Error!", line, data);
	return (path);
}

// Retrieves the image from the xpm file and returns a mask depending on the direction
int	get_image(int direction, char *line, t_data *data)
{
	char	*path;

	path = get_path(line, data);
	data->textures[direction].buffer = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures[direction].width,
			&data->textures[direction].height);
	free(path);
	if (!data->textures[direction].buffer)
		exit_pars("MLX: Failed to convert xpm to img!", line, data);
	data->textures[direction].address = mlx_get_data_addr(data->textures[direction].buffer,
			&data->textures[direction].bits_per_pixel,
			&data->textures[direction].size_line,
			&data->textures[direction].endian);
	if (!data->textures[direction].address)
		exit_pars("MLX: Failed to get data address!", line, data);
	return (1 << direction);
}
