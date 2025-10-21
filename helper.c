/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:48:15 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 14:45:29 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Returns True if c is a whitespace
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (true);
	return (false);
}

bool	is_wall(const t_data *data, double y, double x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width
		|| data->map.map[(int)y][(int)x] == '1'
		|| data->map.map[(int)y][(int)x] == ' '
		|| data->map.map[(int)y][(int)x] == 'D')
		return (true);
	return (false);
}

bool	is_closed_door(const t_data *data, double y, double x)
{
	if (y > 0 && y < data->map.height && x > 0 && x < data->map.width
		&& data->map.map[(int)y][(int)x] == 'D') //idk
		return (true);
	return (false);
}

bool	is_open_door(const t_data *data, double y, double x)
{
	if (y > 0 && y < data->map.height && x > 0 && x < data->map.width
		&& data->map.map[(int)y][(int)x] == 'd') //idk
		return (true);
	return (false);
}

void	fill_image_buffer(t_image image, int y, int x, int color)
{
	char	*pixel_index;

	if (x >= 0 && y >= 0 && x < image.width && y < image.height)
	{
		pixel_index = image.address
			+ (y * image.size_line) + (x * image.bytes_per_pixel);
		*(int *)pixel_index = color;
	}
}
