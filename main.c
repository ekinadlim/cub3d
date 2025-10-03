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
		pixel_index = image.address + (y * image.size_line) + (x * image.bytes_per_pixel);
		*(int *)pixel_index = color;
	}
}

void	calculate_fixed_values(t_data *data)
{
	int	ray;

	ray = 0;
	data->value.fov_tan_half = tan((FOV * PI_180) / 2.0); //maybe not needed in struct, just do as const in this function
	data->value.proj_plane = data->image.half_width / data->value.fov_tan_half;
	while (ray < WINDOW_WIDTH)
	{
		data->value.ray_direction_x[ray] = (2.0 * ray / (double)WINDOW_WIDTH - 1.0) * data->value.fov_tan_half;
		ray++;
	}
}

void	calculate_and_assign_ray_values(t_data *data, int ray, int *y, int *x)
{
	data->ray.y_vector = data->player.direction_sin + data->value.ray_direction_x[ray] * data->player.direction_right_sin;
	data->ray.x_vector = data->player.direction_cos + data->value.ray_direction_x[ray] * data->player.direction_right_cos;
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

	double true_distance = delta_x * data->player.direction_cos + delta_y * data->player.direction_sin;

	return (true_distance);
}

void	print_3d_ray(t_data *data, int ray)
{
	const double perp_wall_dist = perp_wall_distt(data/* , ray */);

	double wall_height = data->value.proj_plane / perp_wall_dist;

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

	for (int y = wall_start; y < wall_end; y++)
	{
		// --- TEX_Y calculation ---
		int d = y * 256 - WINDOW_HEIGHT * 128 + wall_height * 128;
		int tex_y = ((d * data->textures[data->ray.wall_hit].height) / wall_height) / 256; //signed integer overflow

		if (tex_y < 0) tex_y = 0;
		if (tex_y >= data->textures[data->ray.wall_hit].height) tex_y = data->textures[data->ray.wall_hit].height - 1;

		char *pixel_index = data->textures[data->ray.wall_hit].address +
			(tex_y * data->textures[data->ray.wall_hit].size_line) +
			(tex_x * (data->textures[data->ray.wall_hit].bytes_per_pixel)); //here
		int color = *(int *)pixel_index;
		fill_image_buffer(data->image, y, ray, color);
	}

	for (int y = wall_end; y < WINDOW_HEIGHT; y++)
		fill_image_buffer(data->image, y, ray, data->surface[FLOOR]);  // Floor
}

void	calculate_raycasting_values(t_data *data)
{
	//data->player.direction_in_radians = data->player.direction * PI_180; //not here
	data->player.direction_sin = sin(data->player.direction_in_radians);
	data->player.direction_cos = cos(data->player.direction_in_radians);
	data->player.direction_right_sin = sin((data->player.direction + 90) * PI_180);
	data->player.direction_right_cos = cos((data->player.direction + 90) * PI_180);
}

void	raycasting(t_data *data)
{
	int		ray;
	int		y;
	int		x;

	ray = 0;
	calculate_raycasting_values(data);
	while (ray < WINDOW_WIDTH)
	{
		calculate_and_assign_ray_values(data, ray, &y, &x);
		while (y >= 0 && y < data->map.height && x < data->map.width && data->map.map[y][x] != '1' && data->map.map[y][x] != ' ')
		{
			calculate_next_grid_distance(data, y, x);
			move_ray(data, &y, &x);
			if (data->ray_toggle)
				fill_image_buffer(data->minimap, data->minimap.half_height + (int)((data->ray.y  - data->player.y) * GRID_SIZE * SCALING), data->minimap.half_width + (int)((data->ray.x - data->player.x) * GRID_SIZE * SCALING), COLOR_RAY);
		}
		if (!data->ray_toggle)
			print_2d_ray(data);
		print_3d_ray(data, ray);
		ray++;
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
	static long last_frame_time = 0;
    static double current_fps = 0.0;
    static int frame_count = 0;
    long current_time = get_current_time();
    
    // Initialize on first run
    if (last_frame_time == 0)
        last_frame_time = current_time;
    
    // Calculate FPS based on time since last frame
    long frame_time = current_time - last_frame_time;
    if (frame_time > 0)
    {
        double instantaneous_fps = 1000.0 / frame_time;
        
        // Only update displayed FPS every 30 frames
        frame_count++;
        if (frame_count >= 30)
        {
            current_fps = instantaneous_fps;
            frame_count = 0;
        }
    }
    
    last_frame_time = current_time;
	//if (get_current_time() - data->time_reference > 1000 / FPS)
	//{
		//current_time = get_current_time();
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
		//if (data->movement_happend || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed
		print_map(data);
		//counter++;
	//}

	char fps_text[32];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.0f", current_fps);  // %.0f removes decimals
    mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, fps_text);
	return (0);
}

void	start_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data->win == NULL)
		exit_cub3d(NULL);
	data->image.buffer = mlx_new_image(data->mlx, data->image.width, data->image.height);
	if (data->image.buffer == NULL)
		exit_cub3d(NULL);
	data->image.address = mlx_get_data_addr(data->image.buffer, &data->image.bytes_per_pixel, &data->image.size_line, &data->image.endian);
	data->image.bytes_per_pixel /= 8;
	if (data->image.address == NULL)
		exit_cub3d(NULL);
	data->minimap.buffer = mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (data->minimap.buffer == NULL)
		exit_cub3d(NULL);
	data->minimap.address = mlx_get_data_addr(data->minimap.buffer, &data->minimap.bytes_per_pixel, &data->minimap.size_line, &data->minimap.endian);
	data->minimap.bytes_per_pixel /= 8;
	if (data->minimap.address == NULL)
		exit_cub3d(NULL);
	mlx_do_key_autorepeatoff(data->mlx); //no fail possible?
	//mlx_mouse_hide(data->mlx, data->win); //this is the only mlx function that leaks, shouldnt use it when submitting
	mlx_mouse_move(data->mlx, data->win, data->image.half_width, data->image.half_height);
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
	data->image.half_height = data->image.height / 2;
	data->image.width = WINDOW_WIDTH;
	data->image.half_width = data->image.width / 2;
	data->minimap.height = MINIMAP_HEIGHT * SCALING;
	data->minimap.half_height = data->minimap.height / 2;
	data->minimap.width = MINIMAP_WIDTH * SCALING;
	data->minimap.half_width = data->minimap.width / 2;
	data->minimap_toggle = true;
	//data->value.fov_tan_half = tan((FOV * PI_180) / 2.0);
	//data->value.proj_plane = data->image.half_width / data->value.fov_tan_half;
	calculate_fixed_values(data);
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
