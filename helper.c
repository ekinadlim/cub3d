/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:48:15 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/23 17:21:35 by apartowi         ###   ########.fr       */
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
	if (data->map.map)
	{
		i = 0;
		while (i < data->map.height) //correct?
		{
			if (data->map.map[i])
				free (data->map.map[i]);
			i++;
		}
		free (data->map.map);
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

void	free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i]) //needs testing
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

// Returns True if c is a whitespace
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (true);
	return (false);
}
