#include "header.h"

void	copy_minimap_to_image(t_data *data)
{
	int		i;
	int		j;
	char	*pixel_index;
	int		color;

	fill_image_buffer(data->minimap, data->minimap.half_height, data->minimap.half_width, COLOR_PLAYER);
	i = 0;
	while (i < data->minimap.height)
	{
		j = 0;
		while (j < data->minimap.width)
		{
			pixel_index = data->minimap.address + (i * data->minimap.size_line) + (j * data->minimap.bytes_per_pixel);
			color = *(int *)pixel_index;
			fill_image_buffer(data->image, MINIMAP_POS_Y + i, MINIMAP_POY_X + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_ray(t_data *data)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + 
									(data->ray.y - data->player.y) * (data->ray.y - data->player.y));
	int steps = (int)(total_distance * data->value.scaled_grid_size);

	if (steps <= 0)
	{
		printf("AAAAAAA: steps = %d\n", steps);
		//steps = 1;
	}

	for (int i = 0; i <= steps; i += 10) {
		double progress = (double)i / steps; //goes from from 0 to 1, so from player position to ray position
		double draw_x = progress * (data->ray.x - data->player.x);
		double draw_y = progress * (data->ray.y - data->player.y);

		if (data->minimap.half_height + (int)(draw_y * data->value.scaled_grid_size) >= data->minimap.height || data->minimap.half_width + (int)(draw_x * data->value.scaled_grid_size) >= data->minimap.width
			|| data->minimap.half_height + (int)(draw_y * data->value.scaled_grid_size) < 0 || data->minimap.half_width + (int)(draw_x * data->value.scaled_grid_size) < 0)
		{
			break ;
		}
		fill_image_buffer(data->minimap, data->minimap.half_height + (int)(draw_y * data->value.scaled_grid_size), data->minimap.half_width + (int)(draw_x * data->value.scaled_grid_size), COLOR_RAY);
	}
}

static int	get_minimap_grid_color(const t_data *data, const double real_y, const double real_x)
{
	int	color;

	if (real_y < 0 || real_x < 0 || real_y >= data->map.height || real_x >= data->map.width)
		color = COLOR_VOID;
	else if (data->map.map[(int)real_y][(int)real_x] == '1')
		color = COLOR_WALL;
	else if (data->map.map[(int)real_y][(int)real_x] == '0')
		color = COLOR_FLOOR;
	else
		color = COLOR_VOID;
	return (color);
}

static void	draw_minimap_pixel(t_data *data, const int map_y_x[2], const double current_y_x[2], const double offset_step)
{
	double	current_offset_y;
	double	current_offset_x;
	int		pixel_y;
	int		pixel_x;

	current_offset_y = 0;
	pixel_y = 0;
	while (pixel_y < data->value.scaled_grid_size)
	{
		current_offset_x = 0;
		pixel_x = 0;
		while (pixel_x < data->value.scaled_grid_size)
		{
			fill_image_buffer(data->minimap, pixel_y + (map_y_x[0] * data->value.scaled_grid_size), pixel_x + (map_y_x[1] * data->value.scaled_grid_size), get_minimap_grid_color(data, current_y_x[0] + current_offset_y, current_y_x[1] + current_offset_x));
			current_offset_x += offset_step;
			pixel_x++;
		}
		current_offset_y += offset_step;
		pixel_y++;
	}
}

void	draw_minimap_grid(t_data *data)
{
	const double	offset_step = 0.1 / SCALING;
	const double	starting_x = data->player.x - (GRID_COUNT / 2);
	double			current_y_x[2];
	int				map_y_x[2];

	current_y_x[0] = data->player.y - (GRID_COUNT / 2);
	map_y_x[0] = 0;
	while (map_y_x[0] < GRID_COUNT)
	{
		current_y_x[1] = starting_x;
		map_y_x[1] = 0;
		while (map_y_x[1] < GRID_COUNT)
		{
			draw_minimap_pixel(data, map_y_x, current_y_x, offset_step);
			current_y_x[1]++;
			map_y_x[1]++;
		}
		current_y_x[0]++;
		map_y_x[0]++;
	}
}
