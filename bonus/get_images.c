/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:02:58 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 19:41:15 by eadlim           ###   ########.fr       */
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

static void	xpm_to_img(char *path, t_image *tex_frame, t_data *data)
{
	tex_frame->buffer = mlx_xpm_file_to_image(data->mlx, path,
			&tex_frame->width, &tex_frame->height);
	free(path);
	if (!tex_frame->buffer)
		exit_pars("MLX: Failed to convert xpm to img!", data);
	tex_frame->address = mlx_get_data_addr(tex_frame->buffer,
			&tex_frame->bytes_per_pixel, &tex_frame->size_line,
			&tex_frame->endian);
	tex_frame->bytes_per_pixel /= 8;
	if (!tex_frame->address)
		exit_pars("MLX: Failed to get data address!", data);
}

// Retrieves the image from the xpm file
// and returns a mask depending on the dir(ection)
int	get_images(int type, t_data *data)
{
	char	*path;
	size_t	i;
	size_t	frame;

	i = 2;
	frame = 0;
	if ((1 << type) & data->filemask)
		exit_pars("Multiple occurance of the same element!", data);
	while (1)
	{
		if (frame >= MAX_ANIMATION_FRAMES)
			exit_pars("Too many frames foo", data);
		path = get_path(data, &i);
		if (!path && !data->animation[type].texture[0].buffer)
			exit_pars("Missing path", data);
		if (!path)
			break ;
		xpm_to_img(path, &data->animation[type].texture[frame], data);
		frame++;
		data->animation[type].frame_amount = frame;
	}
	return (1 << type);
}
