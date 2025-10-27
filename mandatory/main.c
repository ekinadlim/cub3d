/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:34:08 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/09 17:28:35 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	game_loop(t_data *data)
{
	long	current_time;

	if (FPS == UNLIMITED
		|| get_current_time() - data->time_reference > 1000 / FPS)
	{
		current_time = get_current_time();
		data->delta_time = (current_time - data->time_reference) / 1000.0;
		data->time_reference = current_time;
		if (data->keys['j'] && !data->keys['l'])
			turn_left(data, TURN_SPEED * data->delta_time);
		if (data->keys['l'] && !data->keys['j'])
			turn_right(data, TURN_SPEED * data->delta_time);
		if (data->keys['a'] && !data->keys['d'])
			move_left(data);
		if (data->keys['d'] && !data->keys['a'])
			move_right(data);
		if (data->keys['w'] && !data->keys['s'])
			move_forward(data);
		if (data->keys['s'] && !data->keys['w'])
			move_back(data);
		render_game(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	init_data();
	data = get_data();
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d("MLX: Failed to init mlx!");
	parsing(argc, argv, data);
	calculate_fixed_values(data);
	start_mlx(data);
	mlx_loop(data->mlx);
	return (0);
}
