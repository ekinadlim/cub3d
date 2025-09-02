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

void	calculate_and_assign_ray_values(t_data *data, int ray, int *y, int *x)
{
	data->ray.direction = data->player.direction + ((2.0 * ray / WINDOW_WIDTH - 1.0) * (FOV / 2));
	data->ray.radian = data->ray.direction * (M_PI / 180);
	//data->ray.y_vector = sin(data->ray.radian);
	//data->ray.x_vector = cos(data->ray.radian);
	data->ray.y_vector = sin(data->player.direction * M_PI / 180.0) + (2.0 * ray / (double)WINDOW_WIDTH - 1.0) * sin((data->player.direction + 90) * M_PI / 180.0);
	data->ray.x_vector = cos(data->player.direction * M_PI / 180.0) + (2.0 * ray / (double)WINDOW_WIDTH - 1.0) * cos((data->player.direction + 90) * M_PI / 180.0);
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

void	move_ray(t_data *data, int *y, int *x, int *side)
{
	if (data->ray.next_y_grid_distance < data->ray.next_x_grid_distance)
	{
		data->ray.y += data->ray.next_y_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_y_grid_distance * data->ray.x_vector;
		if (data->ray.y_vector > 0)
			(*y)++;
		else
			(*y)--;
		*side = 1;
	}
	else
	{
		data->ray.y += data->ray.next_x_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_x_grid_distance * data->ray.x_vector;
		if (data->ray.x_vector > 0)
			(*x)++;
		else
			(*x)--;
		*side = 0;
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

		fill_image_buffer(data->minimap, (int)(draw_y * TILE_SIZE), (int)(draw_x * TILE_SIZE), 0xFFFF00);
	}
}

double perp_wall_distt(t_data *data)
{
	double delta_x = data->ray.x - data->player.x;
	double delta_y = data->ray.y - data->player.y;
	double ray_angle = atan2(delta_y, delta_x) - (data->player.direction * M_PI / 180.0);
	double true_distance = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(ray_angle);
	return true_distance;
}

void	print_3d_ray(t_data *data, int ray, double perp_wall_dist)
{
	double total_distance = sqrt((data->ray.x - data->player.x) * (data->ray.x - data->player.x) + (data->ray.y - data->player.y) * (data->ray.y - data->player.y));

	double ray_angle = data->ray.direction - data->player.direction;

	double true_distance = total_distance * cos(ray_angle * M_PI / 180.0);
	(void)perp_wall_dist;
	(void)true_distance;

	//double wall_height = WINDOW_HEIGHT / true_distance;
	double wall_height = WINDOW_HEIGHT / perp_wall_distt(data);

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
	if (wall_end >= WINDOW_HEIGHT)
		wall_end = WINDOW_HEIGHT;

	int y;
	for (y = wall_start; y < wall_end; y++) {
		fill_image_buffer(data->image, y, ray, 0xFFFFFF);  // White wall
	}
	for (; y < WINDOW_HEIGHT; y++) {
		fill_image_buffer(data->image, y, ray, 0x808080);  // Grey floor
	}
}

void	raycasting(t_data *data)
{
	int	ray;
	int		y;
	int		x;
	int	side;

	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		calculate_and_assign_ray_values(data, ray, &y, &x);
		while (map[y][x] != '1') //!hit_wall (maybe && != ['2'/' '])
		{
			calculate_next_grid_distance(data, y, x);
			move_ray(data, &y, &x, &side);
			fill_image_buffer(data->minimap, (int)(data->ray.y * TILE_SIZE), (int)(data->ray.x * TILE_SIZE), 0xFFFF00);
		}
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = fabs((x - data->player.x + (1 - (data->ray.x_vector > 0 ? 1 : -1)) / 2) / data->ray.x_vector);
		else
			perp_wall_dist = fabs((y - data->player.y + (1 - (data->ray.y_vector > 0 ? 1 : -1)) / 2) / data->ray.y_vector);
		print_3d_ray(data, ray, perp_wall_dist);
		ray += 1;
	}
}

void	clear_screen(t_image image) //maybe not needed since every pixel will be overwritten when implementing floor and ceiling
{
	int	i;
	int	j;

	i = 0;
	while(i < image.height)
	{
		j = 0;
		while (j < image.width)
		{
			fill_image_buffer(image, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void copy_minimap_to_image(t_data *data)
{
	int		i;
	int		j;
	char	*pixel_index;
	int		color;

	fill_image_buffer(data->minimap, (int)(data->player.y * TILE_SIZE) , (int)(data->player.x * TILE_SIZE), 0xFF0000); //Player
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

void	print_minimap_grid(t_data *data)
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
					fill_image_buffer(data->minimap, (i * TILE_SIZE) + a, (j * TILE_SIZE) + b, color);
					b++;
				}
				a++;
			}
			j++;
		}
		i++;
	}
}

void	print_map(t_data *data)
{
	clear_screen(data->image);

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
	if (map[(int)y][(int)x] == '1'|| map[(int)y][(int)x] == '2') //change to ' '
		return (false);
	return (true);
}

void	move_forward(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (4 * data->delta_time);
	double y = sin(radian) * (4 * data->delta_time);

	if (check_if_wall(data, data->player.y + y, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (check_if_wall(data, data->player.y, data->player.x + x))
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	move_backwards(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (-4 * data->delta_time);
	double y = sin(radian) * (-4 * data->delta_time);

	if (check_if_wall(data, data->player.y + y, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (check_if_wall(data, data->player.y, data->player.x + x))
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

	if (check_if_wall(data, data->player.y + y, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (check_if_wall(data, data->player.y, data->player.x + x))
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

	if (check_if_wall(data, data->player.y + y, data->player.x))
	{
		data->player.y += y;
		data->movement_happend = true;
	}
	if (check_if_wall(data, data->player.y, data->player.x + x))
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}

void	turn_left(t_data *data, int speed)
{
	data->player.direction -= speed * data->delta_time,
	data->movement_happend = true;
	if (data->player.direction < 0)
		data->player.direction += 360;
}

void	turn_right(t_data *data, int speed)
{
	data->player.direction += speed * data->delta_time,
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
	int delta_x = x - WINDOW_WIDTH / 2;

	(void)y;
	if (delta_x < 0)
		turn_left(data, -(delta_x * 5));
	else if (delta_x > 0)
		turn_right(data, delta_x * 5);
	if (x != WINDOW_WIDTH / 2 || y != WINDOW_HEIGHT / 2)
		mlx_mouse_move(data->mlx, data->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
	parsing(argc, argv, data);
 	data->player.y = 2;
	data->player.x = 2.5;
	data->time_reference = get_current_time();
	data->image.height = WINDOW_HEIGHT;
	data->image.width = WINDOW_WIDTH;
	data->minimap.height = MINIMAP_HEIGHT;
	data->minimap.width = MINIMAP_WIDTH;
	data->minimap_toggle = true;
	start_mlx(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
	print_map(data);
	mlx_loop(data->mlx);
}
