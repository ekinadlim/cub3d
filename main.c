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

	//double step = (double)data->textures[data->ray.wall_hit].height / wall_height; // tex pixels per screen pixel
	//double tex_pos = (wall_start - WINDOW_HEIGHT / 2.0 + wall_height / 2.0) * step;
	for (int y = wall_start; y < wall_end; y++)
	{
		// --- TEX_Y calculation ---
		int d = y * 256 - WINDOW_HEIGHT * 128 + wall_height * 128;
		int tex_y = ((d * data->textures[data->ray.wall_hit].height) / wall_height) / 256; //signed integer overflow

		/* int new_tex_y = (int)tex_pos;
		if (new_tex_y < 0) new_tex_y = 0;
		if (new_tex_y >= data->textures[data->ray.wall_hit].height) new_tex_y = data->textures[data->ray.wall_hit].height - 1; // clamp (use & if power-of-two)
		tex_pos += step; */
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
			//maybe toggle if grid view for minimap or wave (print_2d_ray)
			if (data->ray_toggle)
				fill_image_buffer(data->minimap, data->minimap.height / 2 + (int)((data->ray.y  - data->player.y) * GRID_SIZE * SCALING), data->minimap.width / 2 + (int)((data->ray.x - data->player.x) * GRID_SIZE * SCALING), COLOR_RAY);
		}
		//maybe toggle if grid view for minimap or wave (print_2d_ray)
		if (!data->ray_toggle)
			print_2d_ray(data);
		print_3d_ray(data, ray);
		ray += 1;
	}
}

void	print_map(t_data *data)
{
	if (data->minimap_toggle)
		print_minimap_grid(data);

	raycasting(data);

	if (data->minimap_toggle)
		copy_minimap_to_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.buffer, 0, 0);
	data->movement_happend = false;
}

bool	check_if_wall(t_data *data, double y, double x) //better name (is_grid_valid) or something like that
{
	(void)data;
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width || data->map.map[(int)y][(int)x] == '1'|| data->map.map[(int)y][(int)x] == ' ')
		return (false);
	return (true);
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
		if (data->movement_happend || data->keys['m']|| data->keys['r'])
			print_map(data);
	}
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
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d(NULL);
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
