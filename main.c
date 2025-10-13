/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:34:08 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:34:09 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* int	game_loop(t_data *data)
{
	static long last_frame_time = 0;
    static double current_fps = 0.0;
    static int frame_count = 0;
    long current_time = get_current_time();
    
    // Initialize on first run
    if (last_frame_time == 0)
        last_frame_time = current_time;
    
    // Calculate FPS based on time since last frame
    long frame_time = current_time - last_frame_time;
    if (frame_time > 0)
    {
        double instantaneous_fps = 1000.0 / frame_time;
        
        // Only update displayed FPS every 30 frames
        frame_count++;
        if (frame_count >= 30)
        {
            current_fps = instantaneous_fps;
            frame_count = 0;
        }
    }
    
    last_frame_time = current_time;
	//if (get_current_time() - data->time_reference > 1000 / FPS)
	//{
		//current_time = get_current_time();
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
			move_backwards(data);
		//if (data->render_required || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed
		render_game(data);
		//counter++;
	//}

	char fps_text[32];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.0f", current_fps);  // %.0f removes decimals
    mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, fps_text);
	return (0);
} */

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
			move_backwards(data);
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
			//printf("%s\n", path);
			data->animation[j][i].buffer = mlx_xpm_file_to_image(data->mlx, path, &data->animation[j][i].width, &data->animation[j][i].height);
			data->animation[j][i].address = mlx_get_data_addr(data->animation[j][i].buffer, &data->animation[j][i].bytes_per_pixel, &data->animation[j][i].size_line, &data->animation[j][i].endian);
			data->animation[j][i].bytes_per_pixel /= 8;
			//printf("%dx%d\n", data->animation[j][i].width, data->animation[j][i].height);
			path[15]++;
			data->animation_frames_amount[j] = i;
			if (data->animation_frames_amount[j] >= MAX_ANIMATION_FRAMES) //???
				exit_cub3d("AAAAAAAAAAAA");
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
