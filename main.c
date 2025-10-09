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
			move_back(data);
		//if (data->render_required || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed
		render_game(data);
		//counter++;
	//}

	char fps_text[32];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.0f", current_fps);  // %.0f removes decimals
    mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, fps_text);
	return (0);
} */

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
	calculate_fixed_values(data);
	start_mlx(data);
	//render_game(data); ???
	mlx_loop(data->mlx);
	return (0);
}
