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

void	init_test_stuff(t_data *data)
{
	data->win_height = 480;
	data->win_width = 640;
	data->player.y = 0;
	data->player.x = 0;
}

void	fill_image_buffer(t_data *data, int y, int x, int color)
{
	char *pixel_index;

	if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
	{
		pixel_index = data->image.address + (y * data->image.size_line) + (x * (data->image.bits_per_pixel / 8));
		*(int *)pixel_index = color;
	}
}
//for testing
int		map_height = 10;
int		map_width = 10;

char	map[10][10] = 
{
	"1111111111",
	"1000000001",
	"1000000001",
	"2101001001",
	"2100000001",
	"2100000001",
	"1001001001",
	"1000000001",
	"1000000001",
	"1111111111",
};

/* void	raycasting2(t_data *data)
{
	double	ray;

	ray = -1;
	while (ray <= 1)
	{
		data->ray.direction = data->player.direction + (ray * (FOV / 2));
		data->ray.radian = data->ray.direction * (M_PI / 180);
		data->ray.y_vector = sin(data->ray.radian);
		data->ray.x_vector = cos(data->ray.radian);
		data->ray.y = data->player.y;
		data->ray.x = data->player.x;
		//printf("ray.y_vector: %.50f ray.x_vector: %.50f\n", data->ray.y_vector, data->ray.x_vector);
		//int distance = 0; //just for printing
		//print_cardinal_dir(data->ray.y_vector, data->ray.x_vector);
		while (1) //!hit_wall
		{
			data->ray.y += data->ray.y_vector * 0.1;
			data->ray.x += data->ray.x_vector * 0.1;
			//boundaries check?
			if (map[(int)data->ray.y][(int)(data->ray.x)] == '1')
			{
				//printf("ray: %f distance: %d\n", ray, distance);
				break ; //hit_wall = true;
			}
			fill_image_buffer(data, (int)(data->ray.y * TILE_SIZE), (int)(data->ray.x * TILE_SIZE), 0xFFFF00);
			//distance++;
		}
		ray += 0.01;
	}
} */

void	calculate_and_assign_ray_values(t_data *data, double ray, int *y, int *x)
{
	data->ray.direction = data->player.direction + ((2.0 * ray / WINDOW_WIDTH - 1.0) * (FOV / 2));
	/* if (data->ray.direction < 0)
		data->ray.direction += 360;
	else if (data->ray.direction > 360)
		data->ray.direction -= 360; */
	data->ray.radian = data->ray.direction * (M_PI / 180);
	data->ray.y_vector = sin(data->ray.radian);
	data->ray.x_vector = cos(data->ray.radian);
	data->ray.y = data->player.y;
	data->ray.x = data->player.x;
	*y = (int)data->ray.y;
	*x = (int)data->ray.x;
}

void	calculate_next_grid_distance(t_data *data, int y, int x)
{
	if(data->ray.y_vector > 0)
	{
		data->ray.next_y_grid_distance = (y + 1 - data->ray.y) / data->ray.y_vector;
	}
	else
	{
		//data->ray.y_vector = 0;
		if (data->ray.y_vector == 0)
		{
			data->ray.next_y_grid_distance = 9999;
			//data->ray.next_y_grid_distance = (data->ray.y - y) / (-data->ray.y_vector);
			//printf("Y NUMBER: %f\n", data->ray.next_y_grid_distance);
		}
		else
			data->ray.next_y_grid_distance = (data->ray.y - y) / (-data->ray.y_vector);
	}
	if(data->ray.x_vector > 0)
	{
		data->ray.next_x_grid_distance = (x + 1 - data->ray.x) / data->ray.x_vector;
	}
	else
	{
		if (data->ray.x_vector == 0)
		{
			data->ray.next_x_grid_distance = 9999;
			//data->ray.next_x_grid_distance = (data->ray.x - x) / (-data->ray.x_vector);
			//printf("X NUMBER: %f\n", data->ray.next_x_grid_distance);
		}
		else
			data->ray.next_x_grid_distance = (data->ray.x - x) / (-data->ray.x_vector);
	}
	//printf("X : %f Y : %f\n", data->ray.next_x_grid_distance, data->ray.next_y_grid_distance);
}

void	move_ray(t_data *data, int *y, int *x)
{
	if (data->ray.next_y_grid_distance < data->ray.next_x_grid_distance)
	{
		data->ray.y += data->ray.next_y_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_y_grid_distance * data->ray.x_vector;
		if (data->ray.y_vector > 0)
			(*y)++;
		else
			(*y)--;
	}
	else
	{
		data->ray.y += data->ray.next_x_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_x_grid_distance * data->ray.x_vector;
		if (data->ray.x_vector > 0)
			(*x)++;
		else
			(*x)--;
	}
}

void	print_2d_ray(t_data *data)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + 
									(data->ray.y - data->player.y) * (data->ray.y - data->player.y));
	int steps = (int)(total_distance * TILE_SIZE);

	for (int i = 0; i <= steps; i += 5) {
		double t = (double)i / steps;
		double draw_x = data->player.x + t * (data->ray.x - data->player.x);
		double draw_y = data->player.y + t * (data->ray.y - data->player.y);

		fill_image_buffer(data, (int)(draw_y * TILE_SIZE), (int)(draw_x * TILE_SIZE), 0xFFFF00);
	}
}

//COPILOT
void	print_3d_ray(t_data *data, int ray)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + 
									(data->ray.y - data->player.y) * (data->ray.y - data->player.y));


	double ray_angle = data->ray.direction - data->player.direction;
	//double perp_angle = FOV - ray_angle;

	if (ray == WINDOW_WIDTH / 2)
		printf("MIDDLE_RAY_ANGLE: %f\n", ray_angle);
	if (ray == WINDOW_WIDTH)
		printf("RIGHT_RAY_ANGLE: %f\n", ray_angle);
	
	/* double camera_plane = (total_distance * sin(ray_angle)) / sin(FOV);
	if (ray == WINDOW_WIDTH / 2)
		printf("MIDDLE CAMERA: %f\n", camera_plane);
	if (ray == WINDOW_WIDTH)
		printf("RIGHT CAMERA: %f\n", camera_plane);
	double true_distance = sqrt((total_distance * total_distance) - (2 * total_distance) * camera_plane * cos(FOV - ray_angle) + (camera_plane * camera_plane)); */

	//double true_distance = (total_distance * sin(perp_angle * M_PI / 180.0)) / sin(FOV);
	double true_distance = total_distance * cos(ray_angle * M_PI / 180.0);

	if (ray == WINDOW_WIDTH / 2)
	{
		printf("MIDDLE DISTANCE: %f\n", total_distance);
		printf("LEFT TRUE DISTANCE: %f\n", true_distance);
	}
	if (ray == WINDOW_WIDTH)
	{
		printf("RIGHT DISTANCE: %f\n", total_distance);
		printf("COS: %f\n", cos(ray_angle * M_PI / 180.0));
		printf("RIGHT TRUE DISTANCE: %f\n", true_distance);
	}
	double wall_height = WINDOW_HEIGHT / true_distance;  // Perspective!
	// Clamp wall height to reasonable bounds
	if (wall_height > WINDOW_HEIGHT * 2)  // If wall is too tall
		wall_height = WINDOW_HEIGHT * 2;
	if (wall_height < 1)  // If wall is too small
		wall_height = 1;

	int wall_start = (WINDOW_HEIGHT - wall_height) / 2;
	int wall_end = wall_start + wall_height;

	// Clamp drawing bounds to screen
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > WINDOW_HEIGHT)
		wall_end = WINDOW_HEIGHT;

	for (int y = wall_start; y < wall_end; y++) {
		fill_image_buffer(data, y, ray, 0xFFFFFF);  // White wall
	}
}

void	raycasting(t_data *data)
{
	double	ray;
	int		y;
	int		x;

	ray = 0;
	while (ray <= WINDOW_WIDTH)
	{
		calculate_and_assign_ray_values(data, ray, &y, &x);
		while (map[y][x] != '1') //!hit_wall
		{
			calculate_next_grid_distance(data, y, x);
			move_ray(data, &y, &x);
			fill_image_buffer(data, (int)(data->ray.y * TILE_SIZE), (int)(data->ray.x * TILE_SIZE), 0xFFFF00);
		}
		if (ray == WINDOW_WIDTH / 2)
			printf("MIDDLE: PLAYER_Y: %f, PLAYER_X: %f, RAY_Y: %f, RAY_X: %f\n", data->player.y, data->player.x, data->ray.y, data->ray.x);
		if (ray == WINDOW_WIDTH - 1)
			printf("RIGHT: PLAYER_Y: %f, PLAYER_X: %f, RAY_Y: %f, RAY_X: %f\n", data->player.y, data->player.x, data->ray.y, data->ray.x);
			//print_2d_ray(data);
		print_3d_ray(data, ray);
		ray += 1;
	}
}

void	clear_screen(t_data *data) //maybe not needed since every pixel will be overwritten when implementing floor and ceiling
{
	int	i;
	int	j;

	i = 0;
	while(i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			fill_image_buffer(data, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	print_map(t_data *data)
{
	int	i;
	int	j;
	int	a;
	int b;
	int color;

	clear_screen(data);
	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == '1')
				color = 0x0001F4;
			else if (map[i][j] == '0')
				color = 0x000064;
			else
				color = 0x000000;
			a = 0;
			while (a < TILE_SIZE)
			{
				b = 0;
				while (b < TILE_SIZE)
				{
					fill_image_buffer(data, (i * TILE_SIZE) + a, (j * TILE_SIZE) + b, color);
					b++;
				}
				a++;
			}
			j++;
		}
		i++;
	}

	raycasting(data);

	fill_image_buffer(data, (int)(data->player.y * TILE_SIZE) , (int)(data->player.x * TILE_SIZE), 0xFF0000);

	mlx_put_image_to_window(data->mlx, data->win, data->image.buffer, 0, 0);
}

bool	check_if_wall(t_data *data, double y, double x)
{
	(void)data;
	if (map[(int)y][(int)x] == '1'|| map[(int)y][(int)x] == '2')
		return (false);
	return (true);
}

void	move_forward(t_data *data, bool *change)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * 0.1;
	double y = sin(radian) * 0.1;

	if (check_if_wall(data, data->player.y + y, data->player.x + x))
	{
		data->player.x += x;
		data->player.y += y;
		*change = true;
	}
}

void	move_backwards(t_data *data, bool *change)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * -0.1;
	double y = sin(radian) * -0.1;

	if (check_if_wall(data, data->player.y + y, data->player.x + x))
	{
		data->player.x += x;
		data->player.y += y;
		*change = true;
	}
}

void	move_left(t_data *data, bool *change)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian - (M_PI / 2)) * 0.1;
	double y = sin(radian - (M_PI / 2)) * 0.1;

	if (check_if_wall(data, data->player.y + y, data->player.x + x))
	{
		data->player.x += x;
		data->player.y += y;
		*change = true;
	}
}

void	move_right(t_data *data, bool *change)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian + (M_PI / 2)) * 0.1;
	double y = sin(radian + (M_PI / 2)) * 0.1;

	if (check_if_wall(data, data->player.y + y, data->player.x + x))
	{
		data->player.x += x;
		data->player.y += y;
		*change = true;
	}
}

int	game_loop(t_data *data)
{
	bool	change; //to not always draw if no movement happend

	if (get_current_time() - data->time_reference > 1000 / FPS)
	{
		change = false;
		if (data->keys['j']) //turn left
		{
			data->player.direction -= 5, change = true;
			if (data->player.direction < 0)
				data->player.direction += 360;
			printf("Direction: %f\n", data->player.direction);
		}
		if (data->keys['l']) //turn right
		{
			data->player.direction += 5, change = true;
			if (data->player.direction > 360)
				data->player.direction -= 360;
			printf("Direction: %f\n", data->player.direction);
		}
		if (data->keys['a'])
			move_left(data, &change);
		if (data->keys['d'])
			move_right(data, &change);
		if (data->keys['w'])
			move_forward(data, &change);
		if (data->keys['s'])
			move_backwards(data, &change);
		if (change)
			print_map(data);
		data->time_reference = get_current_time();
	}
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == 'w' || key == KEY_UP)
		data->keys['w'] = true;
	else if (key == 'd' || key == KEY_RIGHT)
		data->keys['d'] = true;
	else if (key == 's' || key == KEY_DOWN)
		data->keys['s'] = true;
	else if (key == 'a' || key == KEY_LEFT)
		data->keys['a'] = true;
	else if (key == 'j')
		data->keys['j'] = true;
	else if (key == 'l')
		data->keys['l'] = true;
	else if (key == 'q' || key == KEY_ESC)
		exit_cub3d(NULL);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 'w' || key == KEY_UP)
		data->keys['w'] = false;
	else if (key == 'd' || key == KEY_RIGHT)
		data->keys['d'] = false;
	else if (key == 's' || key == KEY_DOWN)
		data->keys['s'] = false;
	else if (key == 'a' || key == KEY_LEFT)
		data->keys['a'] = false;
	else if (key == 'j')
		data->keys['j'] = false;
	else if (key == 'l')
		data->keys['l'] = false;
	return (0);
}

void	start_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d(NULL);//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data->win == NULL)
		exit_cub3d(NULL);//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	data->image.buffer = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->image.buffer == NULL)
		exit_cub3d(NULL);
	data->image.address = mlx_get_data_addr(data->image.buffer, &data->image.bits_per_pixel, &data->image.size_line, &data->image.endian);
	if (data->image.address == NULL)
		exit_cub3d(NULL);
}

int main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	
	init_data();
	data = get_data();
	//do small map
	parsing(argc, argv, data);
	data->player.y = 2;
	data->player.x = 2.5;
	data->time_reference = get_current_time();
	start_mlx(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}
