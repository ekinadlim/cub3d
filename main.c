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

void	update_animation_frame(t_data *data)
{
	static long blabla = 0;
	if (blabla == 0)
	{
		blabla = get_current_time();
	}
	for (int i = 0; i < 4; i++)
	{
		data->animation_tracker[i] += data->delta_time * ANIMATION_SPEED;
		if ((int)data->animation_tracker[i])
		{
			data->animation_index[i] += (int)data->animation_tracker[i];
			while (data->animation_index[i] >= data->animation_frames_amount[i]) //animation_count for each texture
				data->animation_index[i] -= data->animation_frames_amount[i];
			data->animation_tracker[i] = data->animation_tracker[i] - (int)data->animation_tracker[i];
		}
	}
	//printf("MS: %ld ,Animation: frame %d, delta_time: %.4f\n", get_current_time() - blabla, data->animation_index[0], data->delta_time);
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

void	load_animations(t_data *data)
{
	//Just to test
	char path[] = "textures/eyeNO/0.xpm";
	for (int j = 0; j < 4; j++)
	{
		if (j == 1)
			path[12] = 'E', path[13] = 'A';
		else if (j == 2)
			path[12] = 'S', path[13] = 'O';
		else if (j == 3)
			path[12] = 'W', path[13] = 'E';
		path[15] = '0';
		for (int i = 0; i < 10; i++)
		{
			if (data->animation_frames_amount[j] >= MAX_ANIMATION_FRAMES) //???
				exit_cub3d("3AAAAAAAAAAAA");
			data->animation[j][i].buffer = mlx_xpm_file_to_image(data->mlx, path, &data->animation[j][i].width, &data->animation[j][i].height);
			if (!data->animation[j][i].buffer)
				exit_cub3d("1AAAAAAAAAAAA");
			data->animation[j][i].address = mlx_get_data_addr(data->animation[j][i].buffer, &data->animation[j][i].bytes_per_pixel, &data->animation[j][i].size_line, &data->animation[j][i].endian);
			if (!data->animation[j][i].address)
				exit_cub3d("2AAAAAAAAAAAA");
			data->animation[j][i].bytes_per_pixel /= 8;
			data->animation_frames_amount[j]++;
			path[15]++;
		}
	}
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
	load_animations(data);
	calculate_fixed_values(data);
	start_mlx(data);
	//render_game(data); ???
	mlx_loop(data->mlx);
	return (0);
}
