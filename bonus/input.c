/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:32:57 by apartowi          #+#    #+#             */
/*   Updated: 2025/10/08 13:32:58 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_press(int key, t_data *data)
{
	if (key == MOVE_FORWARD)
		data->keys['w'] = true;
	else if (key == MOVE_RIGHT)
		data->keys['d'] = true;
	else if (key == MOVE_BACK)
		data->keys['s'] = true;
	else if (key == MOVE_LEFT)
		data->keys['a'] = true;
	else if (key == KEY_LEFT)
		data->keys['j'] = true;
	else if (key == KEY_RIGHT)
		data->keys['l'] = true;
	else if (key == 'm')
		data->minimap_toggle = !data->minimap_toggle;
	else if (key == 'r')
		data->ray_toggle = !data->ray_toggle;
	else if (key == 'f')
		data->flashlight_toggle = !data->flashlight_toggle;
	else if (key == 'q' || key == KEY_ESC)
		exit_cub3d(NULL);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == MOVE_FORWARD)
		data->keys['w'] = false;
	else if (key == MOVE_RIGHT)
		data->keys['d'] = false;
	else if (key == MOVE_BACK)
		data->keys['s'] = false;
	else if (key == MOVE_LEFT)
		data->keys['a'] = false;
	else if (key == KEY_LEFT)
		data->keys['j'] = false;
	else if (key == KEY_RIGHT)
		data->keys['l'] = false;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	const int	delta_x = x - data->image.half_width;

	if (delta_x < 0)
		turn_left(data, -(delta_x * MOUSE_SENSITIVITY));
	else if (delta_x > 0)
		turn_right(data, delta_x * MOUSE_SENSITIVITY);
	if (x != data->image.half_width || y != data->image.half_height)
		mlx_mouse_move(data->mlx, data->win,
			data->image.half_width, data->image.half_height);
	return (0);
}

int	mouse_click(int button, int x, int y, t_data *data)
{
	(void)button;
	mouse_move(x, y, data);
	return (0);
}

int	mouse_release(int button, int x, int y, t_data *data)
{
	(void)button;
	mouse_move(x, y, data);
	return (0);
}
