/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:34:01 by apartowi          #+#    #+#             */
/*   Updated: 2025/11/14 17:16:58 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data(void)
{
	t_data	*data;

	data = get_data();
	ft_memset(data, 0, sizeof(t_data));
	data->time_reference = get_current_time();
	data->image.height = WINDOW_HEIGHT;
	data->image.half_height = data->image.height / 2;
	data->image.width = WINDOW_WIDTH;
	data->image.half_width = data->image.width / 2;
	data->minimap.height = MINIMAP_HEIGHT * SCALING;
	data->minimap.half_height = data->minimap.height / 2;
	data->minimap.width = MINIMAP_WIDTH * SCALING;
	data->minimap.half_width = data->minimap.width / 2;
	data->minimap_toggle = true;
	data->value.scaled_grid_size = GRID_SIZE * SCALING;
}

void	calculate_fixed_values(t_data *data)
{
	const double	fov_tan_half = tan((FOV * PI_180) / 2.0);
	int				ray;

	data->value.proj_plane = data->image.half_width / fov_tan_half;
	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		data->value.ray_direction_x[ray]
			= (2.0 * ray / (double)WINDOW_WIDTH - 1.0) * fov_tan_half;
		ray++;
	}
}

//mlx_mouse_hide(data->mlx, data->win); //this mlx function leaks
static void	call_mlx_hooks(t_data *data)
{
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_mouse_move(data->mlx, data->win,
		data->image.half_width, data->image.half_height);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_click, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
}

void	start_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data->win == NULL)
		exit_cub3d("MLX: Failed to create a new window!");
	data->image.buffer
		= mlx_new_image(data->mlx, data->image.width, data->image.height);
	if (data->image.buffer == NULL)
		exit_cub3d("MLX: Failed to create a new img!");
	data->image.address
		= mlx_get_data_addr(data->image.buffer, &data->image.bytes_per_pixel,
			&data->image.size_line, &data->image.endian);
	data->image.bytes_per_pixel /= 8;
	if (data->image.address == NULL)
		exit_cub3d("MLX: Failed to get data addr!");
	data->minimap.buffer
		= mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (data->minimap.buffer == NULL)
		exit_cub3d("MLX: Failed to create a new img!");
	data->minimap.address
		= mlx_get_data_addr(data->minimap.buffer,
			&data->minimap.bytes_per_pixel, &data->minimap.size_line,
			&data->minimap.endian);
	data->minimap.bytes_per_pixel /= 8;
	if (data->minimap.address == NULL)
		exit_cub3d("MLX: Failed to get data addr!");
	call_mlx_hooks(data);
}
