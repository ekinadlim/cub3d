#include "header.h"

void	init_data(void)
{
	t_data	*data;

	data = get_data();
	ft_memset(data, 0, sizeof(t_data));
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	fill_image_buffer(t_image image, int y, int x, int color)
{
	char *pixel_index;

	if (x >= 0 && y >= 0 && x < image.width && y < image.height) //protection not needed?
	{
		pixel_index = image.address + (y * image.size_line) + (x * (image.bits_per_pixel / 8));
		*(int *)pixel_index = color;
	}
}
//for testing
int		map_height = 10;
int		map_width = 10;

/* char	map[14][25] = 
{
	"1111111111111111111111111",
	"1000000000000000000000001",
	"1000000000000000000000001",
	" 101001000000000000000001",
	" 100000000000000000000001",
	" 100000000000000000000001",
	"1001001000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1000000000000000000000001",
	"1111111111111111111111111",
}; */

/* char	map[14][25] = 
{
	"1111111111111111111111111",
	"1000000000110000000000001",
	"1000000001110000000000001",
	"1001000000000000000000001",
	"1111111110110000011100001",
	"1000000000110000011101111",
	"1111011111111101110000001",
	"1111011111111101110101001",
	"1100000011010101110000001",
	"1000000000000000110000001",
	"1000000000000000110101001",
	"1100000111010101111101111",
	"11110111 1110101 10111101",
	"11111111 1111111 11111111",
}; */

char	map[10][10] = 
{
	"1111111111",
	"1000000001",
	"1000000001",
	"1001001001",
	"1000000001",
	"1000000001",
	"1001001001",
	"1000100001",
	"1000000001",
	"1111111111",
};

/* char	map[5][5] = 
{
	"11111",
	"10001",
	"10101",
	"10001",
	"11111",
}; */

void	calculate_and_assign_ray_values(t_data *data, int ray, int *y, int *x)
{
	data->ray.y_vector = sin(data->player.direction * M_PI / 180.0) + ((2.0 * ray / (double)WINDOW_WIDTH - 1.0) * tan((FOV * M_PI / 180.0) / 2.0)) * sin((data->player.direction + 90) * M_PI / 180.0);
	data->ray.x_vector = cos(data->player.direction * M_PI / 180.0) + ((2.0 * ray / (double)WINDOW_WIDTH - 1.0) * tan((FOV * M_PI / 180.0) / 2.0)) * cos((data->player.direction + 90) * M_PI / 180.0);
	data->ray.y = data->player.y;
	data->ray.x = data->player.x;
	*y = (int)data->ray.y;
	*x = (int)data->ray.x;
}

void	calculate_next_grid_distance(t_data *data, int y, int x)
{
	if (data->ray.y_vector == 0)
		data->ray.next_y_grid_distance = 9999;
	else if(data->ray.y_vector > 0)
		data->ray.next_y_grid_distance = (y + 1 - data->ray.y) / data->ray.y_vector;
	else
		data->ray.next_y_grid_distance = (data->ray.y - y) / (-data->ray.y_vector);
	if (data->ray.x_vector == 0)
		data->ray.next_x_grid_distance = 9999;
	else if(data->ray.x_vector > 0)
		data->ray.next_x_grid_distance = (x + 1 - data->ray.x) / data->ray.x_vector;
	else
		data->ray.next_x_grid_distance = (data->ray.x - x) / (-data->ray.x_vector);
}

void	move_ray(t_data *data, int *y, int *x)
{
	if (data->ray.next_y_grid_distance < data->ray.next_x_grid_distance)
	{
		data->ray.y += data->ray.next_y_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_y_grid_distance * data->ray.x_vector;
		if (data->ray.y_vector > 0)
		{
			(*y)++;
			data->ray.wall_hit = SOUTH;
		}
		else
		{
			(*y)--;
			data->ray.wall_hit = NORTH;
		}
	}
	else
	{
		data->ray.y += data->ray.next_x_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_x_grid_distance * data->ray.x_vector;
		if (data->ray.x_vector > 0)
		{
			(*x)++;
			data->ray.wall_hit = EAST;
		}
		else
		{
			(*x)--;
			data->ray.wall_hit = WEST;
		}
	}
}

void	print_2d_ray(t_data *data)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + 
									(data->ray.y - data->player.y) * (data->ray.y - data->player.y));
	int steps = (int)(total_distance * GRID_SIZE * SCALING);

	for (int i = 0; i <= steps; i += 5) {
		double t = (double)i / steps;
		double draw_x = t * (data->ray.x - data->player.x);
		double draw_y = t * (data->ray.y - data->player.y);

		if (data->minimap.height / 2 + (int)(draw_y * GRID_SIZE * SCALING) >= data->minimap.height || data->minimap.width / 2 + (int)(draw_x * GRID_SIZE * SCALING) >= data->minimap.width
			|| data->minimap.height / 2 + (int)(draw_y * GRID_SIZE * SCALING) < 0 || data->minimap.width / 2 + (int)(draw_x * GRID_SIZE * SCALING) < 0)
		{
			//printf("print_2d_ray\n");
			break;
		}
		fill_image_buffer(data->minimap, data->minimap.height / 2 + (int)(draw_y * GRID_SIZE * SCALING), data->minimap.width / 2 + (int)(draw_x * GRID_SIZE * SCALING), COLOR_RAY);
	}
}

double perp_wall_distt(t_data *data/* , int ray */)
{
	double delta_x = data->ray.x - data->player.x;
	double delta_y = data->ray.y - data->player.y;

	double forward_x = cos(data->player.direction * M_PI / 180.0); //i should probably store this once since it wont change after starting raycasting
	double forward_y = sin(data->player.direction * M_PI / 180.0);

	double true_distance = delta_x * forward_x + delta_y * forward_y;

	/* if (ray == 0)
	{
		printf("delta_x = %f + %f = %f\n", data->ray.x, data->player.x, delta_x);
		printf("delta_y = %f + %f = %f\n", data->ray.y, data->player.y, delta_y);
		printf("forward_x = %f\n", forward_x);
		printf("forward_y = %f\n", forward_y);
		printf("true_distance = %f\n", true_distance);
	} */
	
	return (true_distance);
}

void	print_3d_ray(t_data *data, int ray)
{
	double perp_wall_dist = perp_wall_distt(data/* , ray */);

	double fov_rad = FOV * M_PI / 180.0;
	double proj_plane = (WINDOW_WIDTH / 2.0) / tan(fov_rad / 2.0);

	double wall_height = proj_plane / perp_wall_dist;

	int wall_start = (WINDOW_HEIGHT - wall_height) / 2;
	int wall_end = wall_start + wall_height;

	// Clamp drawing bounds to screen
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= WINDOW_HEIGHT || wall_end < 0)
		wall_end = WINDOW_HEIGHT;

	// --- TEX_X calculation ---
	double wall_x;
	if (data->ray.wall_hit == EAST || data->ray.wall_hit == WEST)
		wall_x = data->player.y + perp_wall_dist * data->ray.y_vector;
	else
		wall_x = data->player.x + perp_wall_dist * data->ray.x_vector;

	if (wall_x < 0)
		wall_x *= -1;
	wall_x = wall_x - (int)wall_x;

	int tex_x = (int)(wall_x * data->textures[data->ray.wall_hit].width);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= data->textures[data->ray.wall_hit].width) tex_x = data->textures[data->ray.wall_hit].width - 1;


	for (int y = 0; y < wall_start; y++)
		fill_image_buffer(data->image, y, ray, data->surface[CEILING]);  // Ceiling

	double step = (double)data->textures[data->ray.wall_hit].height / wall_height; // tex pixels per screen pixel
	double tex_pos = (wall_start - WINDOW_HEIGHT / 2.0 + wall_height / 2.0) * step;
	for (int y = wall_start; y < wall_end; y++)
	{
		// --- TEX_Y calculation ---
		int d = y * 256 - WINDOW_HEIGHT * 128 + wall_height * 128;
		int tex_y = ((d * data->textures[data->ray.wall_hit].height) / wall_height) / 256; //signed integer overflow

		int new_tex_y = (int)tex_pos;
		if (new_tex_y < 0) new_tex_y = 0;
		if (new_tex_y >= data->textures[data->ray.wall_hit].height) new_tex_y = data->textures[data->ray.wall_hit].height - 1; // clamp (use & if power-of-two)
		tex_pos += step;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= data->textures[data->ray.wall_hit].height) tex_y = data->textures[data->ray.wall_hit].height - 1;

		/* if ((y == wall_start || y == wall_end - 1) && (ray == 0 || ray == WINDOW_WIDTH / 2 || ray == WINDOW_WIDTH -1))
			printf("RAY: %d: HEIGHT: %f, TEX_Y: %d, NEW_TEX_Y: %d\n", ray, wall_height, tex_y, new_tex_y); */

		char *pixel_index = data->textures[data->ray.wall_hit].address +
			(tex_y * data->textures[data->ray.wall_hit].size_line) +
			(tex_x * (data->textures[data->ray.wall_hit].bits_per_pixel / 8));
		int color = *(int *)pixel_index;
		fill_image_buffer(data->image, y, ray, color);
	}

	for (int y = wall_end; y < WINDOW_HEIGHT; y++)
		fill_image_buffer(data->image, y, ray, data->surface[FLOOR]);  // Floor
}

void	raycasting(t_data *data)
{
	int	ray;
	int		y;
	int		x;

	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		calculate_and_assign_ray_values(data, ray, &y, &x);
		while (y >= 0 && y < data->map.height && x < data->map.width && data->map.map[y][x] != '1' && data->map.map[y][x] != ' ')
		{
			calculate_next_grid_distance(data, y, x);
			move_ray(data, &y, &x);
			//fill_image_buffer(data->minimap, data->minimap.height / 2 + (int)((data->ray.y  - data->player.y) * GRID_SIZE * SCALING), data->minimap.width / 2 + (int)((data->ray.x - data->player.x) * GRID_SIZE * SCALING), COLOR_RAY);
		}
		print_2d_ray(data);
		print_3d_ray(data, ray);
		ray += 1;
	}
}

void copy_minimap_to_image(t_data *data)
{
	int		i;
	int		j;
	char	*pixel_index;
	int		color;

	fill_image_buffer(data->minimap, data->minimap.height / 2, data->minimap.width / 2, COLOR_PLAYER); //Player
	i = 0;
	while (i < data->minimap.height)
	{
		j = 0;
		while (j < data->minimap.width)
		{
			pixel_index = data->minimap.address + (i * data->minimap.size_line) + (j * (data->minimap.bits_per_pixel / 8));
			color = *(int *)pixel_index;
			fill_image_buffer(data->image, MINIMAP_POS_Y + i, MINIMAP_POY_X + j, color);
			j++;
		}
		i++;
	}
}

/* void	print_minimap_grid(t_data *data)
{
	int	i;
	int	j;
	int	a;
	int b;
	int color;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == '1')
				color = COLOR_WALL;
			else if (map[i][j] == '0')
				color = COLOR_FLOOR;
			else
				color = COLOR_VOID;
			a = 0;
			while (a < GRID_SIZE * SCALING)
			{
				b = 0;
				while (b < GRID_SIZE * SCALING)
				{
					fill_image_buffer(data->minimap, (i * GRID_SIZE * SCALING) + a, (j * GRID_SIZE * SCALING) + b, color);
					b++;
				}
				a++;
			}
			j++;
		}
		i++;
	}
}

void	new_minimap_grid_print(t_data *data)
{
	int offset = GRID_SIZE * SCALING / 2;
	int color;
	double start_y = data->player.y - offset;
	double start_x = data->player.x - offset;
	double end_y = start_y + GRID_SIZE * SCALING;
	double end_x = start_x + GRID_SIZE * SCALING;
	int i;
	int j;


	while (start_y < end_y)
	{
		start_x = end_x - GRID_SIZE * SCALING;
		while (start_x < end_x)
		{
			if (start_y < 0 || start_x < 0 || end_y > map_height || end_x > map_width)
				color = COLOR_VOID;
			else if (map[(int)start_y][(int)start_x] == '1')
				color = COLOR_WALL;
			else if (map[(int)start_y][(int)start_x] == '0')
				color = COLOR_FLOOR;
			else
				color = COLOR_VOID;
			i = 0;
			while (i < GRID_SIZE * SCALING)
			{
				j = 0;
				while (j < GRID_SIZE * SCALING)
				{
					fill_image_buffer(data->minimap, (((start_y) * GRID_SIZE * SCALING) + offset) + i, (((start_x) * GRID_SIZE * SCALING) + offset) + j, color);
					j++;
				}
				i++;
			}
			start_x++;
		}
		start_y++;
	}
} */

void	print_minimap_grid(t_data *data)
{
	/* double origin_offset_y = (data->player.y - (int)data->player.y) * 10;
	double origin_offset_x = (data->player.x - (int)data->player.x) * 10; */

	double current_offset_y = 0;
	double current_offset_x = 0;

	double starting_y = data->player.y - GRID_COUNT / 2; //top left
	double starting_x = data->player.x - GRID_COUNT / 2; //top left

	double current_y = starting_y;
	double current_x = starting_x;

	for (int map_y = 0; map_y < GRID_COUNT; map_y++)
	{
		current_x = starting_x; //lets say 4.8
		for (int map_x = 0; map_x < GRID_COUNT; map_x++)
		{
			current_offset_y = 0;
			for (int pixel_y = 0; pixel_y < GRID_SIZE * SCALING; pixel_y++)
			{
				current_offset_x = 0;
				for (int pixel_x = 0; pixel_x < GRID_SIZE * SCALING; pixel_x++)
				{
					int color;
					double real_y = (current_y + current_offset_y);
					double real_x = (current_x + current_offset_x);
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

					fill_image_buffer(data->minimap, pixel_y + (map_y * GRID_SIZE * SCALING), pixel_x + (map_x * GRID_SIZE * SCALING), color);

					//if (map_y == 0 && map_x == 0)
						//printf("real_y: %d, real_x: %d, pixel_y add: %d, pixel_x add %d, current_y + current_offset_y: %f, current_x + current_offset_x: %f\n", real_y, real_x, pixel_y + (map_y * GRID_SIZE), pixel_x + (map_x * GRID_SIZE), current_y + current_offset_y, current_x + current_offset_x);

					current_offset_x += 0.1 / SCALING;
				}
				current_offset_y += 0.1 / SCALING;
			}
			current_x++;
		}
		current_y++;
	}
}

void	print_map(t_data *data)
{
	//clear_screen(data->image);

	if (data->minimap_toggle)
		print_minimap_grid(data);

	raycasting(data);

	if (data->minimap_toggle)
		copy_minimap_to_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.buffer, 0, 0);
	data->movement_happend = false;
}

bool	check_if_wall(t_data *data, double y, double x)
{
	(void)data;
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width || data->map.map[(int)y][(int)x] == '1'|| data->map.map[(int)y][(int)x] == ' ')
		return (false);
	return (true);
}

/*
void	continuous_collision_detection_y_positive(t_data *data, double y)
{
	int i = 1;
	int valid = 1;

	while (i < y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			valid = 0;
			break ;
		}
		i++;
	}
	printf("Before y: %f\n", y);
	if (!valid)
	{
		y = (int)(data->player.y + i) - data->player.y - 0.2;
	}
	printf("After y: %f\n", y);
	data->player.y += y;
	data->movement_happend = true;
}

void	continuous_collision_detection_y_negative(t_data *data, double y)
{
	int i = -1;
	int valid = 1;

	while (i >= y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			valid = 0;
			break ;
		}
		i--;
	}
	printf("Before y: %f\n", y);
	if (!valid)
	{
		y = (int)(data->player.y + i + 1) - data->player.y + 0.2;
	}
	printf("After y: %f\n", y);
	data->player.y += y;
	data->movement_happend = true;
}

void	continuous_collision_detection_x_positive(t_data *data, double x)
{
	int i = 1;
	int valid = 1;

	while (i < x)
	{
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			valid = 0;
			break ;
		}
		i++;
	}
	printf("Before x: %f\n", x);
	if (!valid)
	{
		x = (int)(data->player.x + i) - data->player.x - 0.2;
	}
	printf("After x: %f\n", x);
	data->player.x += x;
	data->movement_happend = true;
}

void	continuous_collision_detection_x_negative(t_data *data, double x)
{
	int i = -1;
	int valid = 1;

	while (i >= x)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			valid = 0;
			break ;
		}
		i--;
	}
	printf("Before x: %f\n", x);
	if (!valid)
	{
		x = (int)(data->player.x + i + 1) - data->player.x + 0.2;
	}
	printf("After x: %f\n", x);
	data->player.x += x;
	data->movement_happend = true;
}
*/

void ccd_positive_y(t_data *data, double y, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (!is_valid || !check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		y = (int)data->player.y + i - data->player.y - offset;
		printf("1 ccd_positive_y: player.y: %f, wall: %d, y: %f\n", data->player.y, (int)data->player.y + i, y);
	}
	data->player.y += y;
	data->movement_happend = true;
}

void ccd_negative_y(t_data *data, double y, double offset)
{
	int i;
	bool is_valid = true;

	i = -1;
	while (i > y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (!is_valid || !check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		y = (int)data->player.y + i + 1 - data->player.y - offset;
		printf("1 ccd_negative_y: player.y: %f, wall: %d, y: %f\n", data->player.y, (int)data->player.y + i, y);
	}
	data->player.y += y;
	data->movement_happend = true;
}

void	continuous_collision_detection_y(t_data *data, double y, double offset)
{
	if (y >= 1)
		ccd_positive_y(data, y, offset);
	else if (y <= -1)
		ccd_negative_y(data, y, offset);
}

void ccd_positive_x(t_data *data, double x, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < x)
	{
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (!is_valid || !check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		x = (int)data->player.x + i - data->player.x - offset;
		printf("1 ccd_positive_x: player.x: %f, wall: %d, x: %f\n", data->player.x, (int)data->player.x + i, x);
	}
	data->player.x += x;
	data->movement_happend = true;
}

void ccd_negative_x(t_data *data, double x, double offset)
{
	int i;
	bool is_valid = true;

	i = -1;
	while (i > x)
	{
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (!is_valid || !check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		x = (int)data->player.x + i + 1 - data->player.x - offset;
		printf("1 ccd_negative_x: player.x: %f, wall: %d, x: %f\n", data->player.x, (int)data->player.x + i, x);
	}
	data->player.x += x;
	data->movement_happend = true;
}

void	continuous_collision_detection_x(t_data *data, double x, double offset)
{
	if (x >= 1)
		ccd_positive_x(data, x, offset);
	else if (x <= -1)
		ccd_negative_x(data, x, offset);
}

void	move_forward(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (4 * data->delta_time);
	double y = sin(radian) * (4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (y <= -1 || y >= 1)
	{
		continuous_collision_detection_y(data, y, offset);
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		//printf("player.y: %f, y: %f\n", data->player.y, y);
		data->player.y += y;
		data->movement_happend = true;
	}
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, x, offset);
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		//printf("player.x: %f, x: %f\n", data->player.x, x);
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	move_backwards(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (-4 * data->delta_time);
	double y = sin(radian) * (-4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (y <= -1 || y >= 1)
	{
		continuous_collision_detection_y(data, y, offset);
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, x, offset);
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	move_left(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian - (M_PI / 2)) * (4 * data->delta_time);
	double y = sin(radian - (M_PI / 2)) * (4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (y <= -1 || y >= 1)
	{
		continuous_collision_detection_y(data, y, offset);
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, x, offset);
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	move_right(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian + (M_PI / 2)) * (4 * data->delta_time);
	double y = sin(radian + (M_PI / 2)) * (4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (y <= -1 || y >= 1)
	{
		continuous_collision_detection_y(data, y, offset);
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, x, offset);
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	turn_left(t_data *data, int speed)
{
	//printf("speed: %d * delta_time: %f = %f\n", speed, data->delta_time, speed * data->delta_time);
	data->player.direction -= speed * data->delta_time;
	data->movement_happend = true;
	if (data->player.direction < 0)
		data->player.direction += 360;
}

void	turn_right(t_data *data, int speed)
{
	//printf("speed: %d * delta_time: %f = %f\n", speed, data->delta_time, speed * data->delta_time);
	data->player.direction += speed * data->delta_time;
	data->movement_happend = true;
	if (data->player.direction > 360)
		data->player.direction -= 360;
}

int	game_loop(t_data *data)
{
	long	current_time;

	if (get_current_time() - data->time_reference > 1000 / FPS)
	{
		current_time = get_current_time();
		data->delta_time = (current_time - data->time_reference) / 1000.0;
		data->time_reference = current_time;
		if (data->keys['j'] && !data->keys['l'])
			turn_left(data, 150);
		if (data->keys['l'] && !data->keys['j'])
			turn_right(data, 150);
		if (data->keys['a'] && !data->keys['d'])
			move_left(data);
		if (data->keys['d'] && !data->keys['a'])
			move_right(data);
		if (data->keys['w'] && !data->keys['s'])
			move_forward(data);
		if (data->keys['s'] && !data->keys['w'])
			move_backwards(data);
		if (data->movement_happend || data->keys['m'])
			print_map(data);
	}
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == 'w')
		data->keys['w'] = true;
	else if (key == 'd')
		data->keys['d'] = true;
	else if (key == 's')
		data->keys['s'] = true;
	else if (key == 'a')
		data->keys['a'] = true;
	else if (key == KEY_LEFT)
		data->keys['j'] = true;
	else if (key == KEY_RIGHT)
		data->keys['l'] = true;
	else if (key == 'm' && !data->keys['m'])
	{
		data->keys['m'] = true;
		data->minimap_toggle = !data->minimap_toggle;
	}
	else if (key == 'q' || key == KEY_ESC)
		exit_cub3d(NULL);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 'w')
		data->keys['w'] = false;
	else if (key == 'd')
		data->keys['d'] = false;
	else if (key == 's')
		data->keys['s'] = false;
	else if (key == 'a')
		data->keys['a'] = false;
	else if (key == KEY_LEFT)
		data->keys['j'] = false;
	else if (key == KEY_RIGHT)
		data->keys['l'] = false;
	else if (key == 'm')
		data->keys['m'] = false;
	return (0);
}

int mouse_move(int x, int y, t_data *data)
{
	static int half_window_width = WINDOW_WIDTH / 2;
	static int half_window_height = WINDOW_HEIGHT / 2;
	int delta_x = x - half_window_width;

	if (delta_x < 0)
		turn_left(data, -(delta_x * 3));
	else if (delta_x > 0)
		turn_right(data, delta_x * 3);
	if (x != half_window_width || y != half_window_height)
		mlx_mouse_move(data->mlx, data->win, half_window_width, half_window_height);
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

void	start_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data->win == NULL)
		exit_cub3d(NULL);//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	data->image.buffer = mlx_new_image(data->mlx, data->image.width, data->image.height);
	if (data->image.buffer == NULL)
		exit_cub3d(NULL);
	data->image.address = mlx_get_data_addr(data->image.buffer, &data->image.bits_per_pixel, &data->image.size_line, &data->image.endian);
	if (data->image.address == NULL)
		exit_cub3d(NULL);
	data->minimap.buffer = mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (data->minimap.buffer == NULL)
		exit_cub3d(NULL);
	data->minimap.address = mlx_get_data_addr(data->minimap.buffer, &data->minimap.bits_per_pixel, &data->minimap.size_line, &data->minimap.endian);
	if (data->minimap.address == NULL)
		exit_cub3d(NULL);
	mlx_do_key_autorepeatoff(data->mlx); //no fail possible?
	//mlx_mouse_hide(data->mlx, data->win); //this is the only mlx function that leaks, shouldnt use it when submitting
	mlx_mouse_move(data->mlx, data->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

int main(int argc, char **argv)
{
	t_data	*data;
	
	init_data();
	data = get_data();
	//do small map
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d(NULL);//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	parsing(argc, argv, data);
	data->time_reference = get_current_time();
	data->image.height = WINDOW_HEIGHT;
	data->image.width = WINDOW_WIDTH;
	data->minimap.height = MINIMAP_HEIGHT * SCALING;
	data->minimap.width = MINIMAP_WIDTH * SCALING;
	data->minimap_toggle = true;
	start_mlx(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_click, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
	print_map(data);
	mlx_loop(data->mlx);
}
