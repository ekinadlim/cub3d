/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:34:27 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:34:28 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Exit function for the parsing
void	exit_pars(char *err_msg, t_data *data)
{
	if (data)
	{
		if (data->pars.fd > 0)
		{
			get_next_line(data->pars.fd, true);
			close(data->pars.fd);
		}
		if (data->pars.line)
		{
			free(data->pars.line);
			data->pars.line = NULL;
		}
	}
	exit_cub3d(err_msg);
}

static void	free_2d_array(char ***array)
{
	size_t	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

static void	destroy_textures_and_free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i].buffer)
			mlx_destroy_image(data->mlx, data->textures[i].buffer);
		i++;
	}
	//free_2d_array(&data->map.map);
}

static void	destroy_animation_and_free_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < data->animation_frames_amount[i])
		{
			if (data->animation[i][j].buffer)
				mlx_destroy_image(data->mlx, data->animation[i][j].buffer);
			else
				break ;
			j++;
		}
		i++;
	}
	free_2d_array(&data->map.map);
}

// Error Message format: "Error\n<error_msg>\n"
// If there is no error_msg being passed nothing will be printed
int	exit_cub3d(char *error_msg)
{
	t_data	*data;

	if (error_msg)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	data = get_data();
	if (data->image.buffer)
		mlx_destroy_image(data->mlx, data->image.buffer);
	if (data->minimap.buffer)
		mlx_destroy_image(data->mlx, data->minimap.buffer);
	destroy_textures_and_free_map(data); //not needed
	destroy_animation_and_free_map(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_do_key_autorepeaton(data->mlx);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free (data->mlx);
	if (error_msg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
