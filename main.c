#include "header.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

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

int	exit_cub3d(void)
{
	t_data	*data;

	data = get_data();
	//call function to free everything
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free (data->mlx);
	exit (0);
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
	"1101001001",
	"2100000001",
	"1100000001",
	"1001001001",
	"1000000001",
	"1000000001",
	"1111111111",
};

void	raycasting(t_data *data)
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
		int distance = 0; //just for printing
		while (1) //!hit_wall
		{
			data->ray.y += data->ray.y_vector * 0.1;
			data->ray.x += data->ray.x_vector * 0.1;
			//boundaries check?
			if (map[(int)data->ray.y][(int)(data->ray.x)] == '1')
			{
				printf("ray: %f distance: %d\n", ray, distance);
				break ; //hit_wall = true;
			}
			fill_image_buffer(data, (int)(data->ray.y * TILE_SIZE), (int)(data->ray.x * TILE_SIZE), 0xFFFF00);
			distance++;
		}
		ray += 0.01;
	}
}

void	print_map(t_data *data)
{
	int	i;
	int	j;
	int	a;
	int b;
	int color;

	data->image.buffer = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); //check fail
	data->image.address = mlx_get_data_addr(data->image.buffer, &data->image.bits_per_pixel, &data->image.size_line, &data->image.endian);
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
	mlx_destroy_image(data->mlx, data->image.buffer);
}

bool	check_if_wall(t_data *data, double y, double x)
{
	(void)data;
	if (map[(int)y][(int)x] == '1')
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
		exit_cub3d();
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

int main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init_data();
	data = get_data();
	//do small map
	data->player.y = 2;
	data->player.x = 2.5;
	data->time_reference = get_current_time();
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d();//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data->win == NULL)
		exit_cub3d();//free (maybe use exit_cub3d() and pass an exit status for function fail or normal exit?)
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}