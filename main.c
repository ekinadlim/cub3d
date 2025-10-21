/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:34:08 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/21 18:59:15 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_animation_frame(t_data *data)
{
	int	i;
	/* static long blabla = 0;
	if (blabla == 0)
	{
		blabla = get_current_time();
	} */
	i = 0;
	while (i < 4)
	{
		data->animation[i].tracker += data->delta_time * ANIMATION_SPEED;
		if ((int)data->animation[i].tracker)
		{
			data->animation[i].index += (int)data->animation[i].tracker;
			while (data->animation[i].index >= data->animation[i].frame_amount)
				data->animation[i].index -= data->animation[i].frame_amount;
			data->animation[i].tracker
				= data->animation[i].tracker - (int)data->animation[i].tracker;
		}
		i++;
	}
	//printf("%ld: Animation: frame %d, delta_time: %.4f\n", get_current_time() - blabla, data->animation.index[0], data->delta_time);
}

int	game_loop(t_data *data)
{
	long	current_time;

	if (FPS == UNLIMITED
		|| get_current_time() - data->time_reference > 1000 / FPS)
	{
		current_time = get_current_time();
		data->delta_time = (current_time - data->time_reference) / 1000.0;
		data->time_reference = current_time;
		update_animation_frame(data);
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
		//if (data->render_required || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed???
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

	data->door_texture.buffer = mlx_xpm_file_to_image(data->mlx,
				"textures/eyeNO/0.xpm", &data->door_texture.width,
				&data->door_texture.height);
	if (!data->door_texture.buffer)
		exit_pars("MLX: Failed to convert xpm to img!", data);
	data->door_texture.address = mlx_get_data_addr(data->door_texture.buffer,
			&data->door_texture.bytes_per_pixel,
			&data->door_texture.size_line,
			&data->door_texture.endian);
	data->door_texture.bytes_per_pixel /= 8;
	if (!data->door_texture.address)
		exit_pars("MLX: Failed to get data address!", data);

	calculate_fixed_values(data);
	start_mlx(data);
	mlx_loop(data->mlx);
	return (0);
}
