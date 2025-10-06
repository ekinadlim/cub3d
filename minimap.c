#include "header.h"

void copy_minimap_to_image(t_data *data)
{
	int		i;
	int		j;
	char	*pixel_index;
	int		color;

	fill_image_buffer(data->minimap, data->minimap.half_height, data->minimap.half_width, COLOR_PLAYER); //Player
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

void	print_2d_ray(t_data *data)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + 
									(data->ray.y - data->player.y) * (data->ray.y - data->player.y));
	int steps = (int)(total_distance * GRID_SIZE * SCALING); //const double scaled_grid_size = GRID_SIZE * SCALING //or just save in struct since it won't change

	if (steps <= 0)
	{
		printf("AAAAAAA: steps = %d\n", steps);
		//steps = 1;
	}

	for (int i = 0; i <= steps; i += 10) {
		double progress = (double)i / steps; //goes from from 0 to 1, so from player position to ray position
		double draw_x = progress * (data->ray.x - data->player.x);
		double draw_y = progress * (data->ray.y - data->player.y);

		if (data->minimap.half_height + (int)(draw_y * GRID_SIZE * SCALING) >= data->minimap.height || data->minimap.half_width + (int)(draw_x * GRID_SIZE * SCALING) >= data->minimap.width
			|| data->minimap.half_height + (int)(draw_y * GRID_SIZE * SCALING) < 0 || data->minimap.half_width + (int)(draw_x * GRID_SIZE * SCALING) < 0)
		{
			//printf("print_2d_ray\n");
			break;
		}
		fill_image_buffer(data->minimap, data->minimap.half_height + (int)(draw_y * GRID_SIZE * SCALING), data->minimap.half_width + (int)(draw_x * GRID_SIZE * SCALING), COLOR_RAY);
	}
}

static inline int	get_minimap_grid_color(t_data *data, double real_y, double real_x)
{
	int	color;
	if (real_y > -1 && real_y < 0)
		real_y = -1;
	if (real_x > -1 && real_x < 0)
		real_x = -1;
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

void	print_minimap_grid(t_data *data)
{
	double current_offset_y = 0;
	double current_offset_x = 0;

	const double starting_y = data->player.y - GRID_COUNT / 2; //top left //y not needed
	const double starting_x = data->player.x - GRID_COUNT / 2; //top left

	double current_y = starting_y;
	double current_x = starting_x;

	for (int map_y = 0; map_y < GRID_COUNT; map_y++)
	{
		current_x = starting_x;
		for (int map_x = 0; map_x < GRID_COUNT; map_x++)
		{
			current_offset_y = 0;
			for (int pixel_y = 0; pixel_y < GRID_SIZE * SCALING; pixel_y++)
			{
				current_offset_x = 0;
				for (int pixel_x = 0; pixel_x < GRID_SIZE * SCALING; pixel_x++)
				{
					fill_image_buffer(data->minimap, pixel_y + (map_y * GRID_SIZE * SCALING), pixel_x + (map_x * GRID_SIZE * SCALING), get_minimap_grid_color(data, current_y + current_offset_y, current_x + current_offset_x));
					current_offset_x += 0.1 / SCALING;
				}
				current_offset_y += 0.1 / SCALING;
			}
			current_x++;
		}
		current_y++;
	}
}
