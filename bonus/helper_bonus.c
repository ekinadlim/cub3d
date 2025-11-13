/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:48:15 by eadlim            #+#    #+#             */
/*   Updated: 2025/11/12 16:07:04 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

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

bool	is_wall(const t_data *data, const double y, const double x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width
		|| data->map.map[(int)y][(int)x] == '1'
		|| data->map.map[(int)y][(int)x] == ' '
		|| data->map.map[(int)y][(int)x] == 'D')
		return (true);
	return (false);
}

void	fill_image_buffer(t_image image,
	const int y, const int x, int color)
{
	t_data	*data;
	char	*pixel_index;
	double	darkness_level;

	if (x >= 0 && y >= 0 && x < image.width && y < image.height)
	{
		pixel_index = image.address
			+ (y * image.size_line) + (x * image.bytes_per_pixel);
		data = get_data();
		if (data->apply_darkness
			&& image.width == WINDOW_WIDTH && image.height == WINDOW_HEIGHT)
		{
			darkness_level = 1;
			if (data->apply_darkness == 1)
				darkness_level = 35;
			else if (data->apply_darkness == 2)
				darkness_level = data->flashlight[y][x];
			color = ((int)(((color >> 16) & 0xFF) / darkness_level) << 16)
				| ((int)(((color >> 8) & 0xFF) / darkness_level) << 8)
				| (int)((color & 0xFF) / darkness_level);
		}
		*(int *)pixel_index = color;
	}
}
