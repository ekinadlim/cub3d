/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:02:58 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/17 17:57:09 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*get_path(t_data *data, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*path;

	while (data->pars.line[*i] && is_whitespace(data->pars.line[*i]))
		(*i)++;
	if (!data->pars.line[*i])
		return (NULL);
	if (*i == 2 || !data->pars.line[*i])
		exit_pars("Wrong Texture Format!", data);
	start = *i;
	while (data->pars.line[*i] && !is_whitespace(data->pars.line[*i]))
		(*i)++;
	len = *i - start;
	while (data->pars.line[*i] && is_whitespace(data->pars.line[*i]))
		(*i)++;
	path = ft_substr(data->pars.line, start, len);
	if (!path)
		exit_pars("Substr: Malloc Error!", data);
	return (path);
}

// Retrieves the image from the xpm file
// and returns a mask depending on the dir(ection)
int	get_image(int dir, int filemask, t_data *data)
{
	char	*path;
	size_t	i;
	size_t	frame;

	i = 2;
	frame = 0;
	if ((1 << dir) & filemask)
		exit_pars("Multiple occurance of the same element!", data);
	while (1)
	{
		if (frame >= MAX_ANIMATION_FRAMES)
			exit_pars("Too many frames foo", data);
		path = get_path(data, &i);
		if (!path)
			break ;
		data->animation.texture[dir][frame].buffer = mlx_xpm_file_to_image(data->mlx,
				path, &data->animation.texture[dir][frame].width,
				&data->animation.texture[dir][frame].height);
		printf("path: %s\n", path);
		free(path);
		if (!data->animation.texture[dir][frame].buffer)
			exit_pars("MLX: Failed to convert xpm to img!", data);
		data->animation.texture[dir][frame].address = mlx_get_data_addr(data->animation.texture[dir][frame].buffer,
				&data->animation.texture[dir][frame].bytes_per_pixel,
				&data->animation.texture[dir][frame].size_line,
				&data->animation.texture[dir][frame].endian);
		data->animation.texture[dir][frame].bytes_per_pixel /= 8;
		if (!data->animation.texture[dir][frame].address)
			exit_pars("MLX: Failed to get data address!", data);
		frame++;
		data->animation.frame_amount[dir] = frame;
	}
	
	return (1 << dir);
}
