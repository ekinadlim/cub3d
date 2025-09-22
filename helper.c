/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:48:15 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/11 13:31:18 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
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
	//call function to free everything
	if (data->image.buffer)
		mlx_destroy_image(data->mlx, data->image.buffer);
	if (data->minimap.buffer)
		mlx_destroy_image(data->mlx, data->minimap.buffer);
	int i = 0;
	while (i < 4)
	{
		if (data->textures[i].buffer)
			mlx_destroy_image(data->mlx, data->textures[i].buffer);
		i++;
	}
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
