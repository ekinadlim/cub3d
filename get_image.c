/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:02:58 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 15:26:18 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_path(t_data *data)
{
	size_t	start;
	size_t	len;
	size_t	i;
	char	*path;

	i = 2;
	while (data->pars.line[i] && is_whitespace(data->pars.line[i]))
		i++;
	if (i == 2 || !data->pars.line[i])
		exit_pars("Wrong Texture Format!", data);
	start = i;
	while (data->pars.line[i] && !is_whitespace(data->pars.line[i]))
		i++;
	len = i - start;
	while (data->pars.line[i])
	{
		if (is_whitespace(data->pars.line[i]))
			i++;
		else
			exit_pars("Wrong Texture Format!", data);
	}
	path = ft_substr(data->pars.line, start, len);
	if (!path)
		exit_pars("Substr: Malloc Error!", data);
	return (path);
}

// Retrieves the image from the xpm file
// and returns a mask depending on the direction
int	get_image(int dir, int filemask, t_data *data)
{
	char	*path;

	if ((1 << dir) & filemask)
		exit_pars("Multiple occurance of the same element!", data);
	path = get_path(data);
	data->textures[dir].buffer = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures[dir].width, &data->textures[dir].height);
	free(path);
	if (!data->textures[dir].buffer)
		exit_pars("MLX: Failed to convert xpm to img!", data);
	data->textures[dir].address = mlx_get_data_addr(data->textures[dir].buffer,
			&data->textures[dir].bytes_per_pixel, &data->textures[dir].size_line,
			&data->textures[dir].endian);
	data->textures[dir].bytes_per_pixel /= 8;
	if (!data->textures[dir].address)
		exit_pars("MLX: Failed to get data address!", data);
	return (1 << dir);
}
