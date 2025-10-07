#include "header.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_data(void)
{
	t_data	*data;

	data = get_data();
	ft_memset(data, 0, sizeof(t_data));
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
	data->value.scaled_grid_size = GRID_SIZE * SCALING;
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

void	calculate_fixed_values(t_data *data)
{
	const double	fov_tan_half = tan((FOV * PI_180) / 2.0);
	int				ray;

	data->value.proj_plane = data->image.half_width / fov_tan_half;
	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		data->value.ray_direction_x[ray]
			= (2.0 * ray / (double)WINDOW_WIDTH - 1.0) * fov_tan_half;
		ray++;
	}
}

void	calculate_and_assign_ray_values(t_data *data, int ray, int *y, int *x)
{
	data->ray.y_vector = data->player.direction_sin
		+ data->value.ray_direction_x[ray] * data->player.direction_right_sin;
	data->ray.x_vector = data->player.direction_cos
		+ data->value.ray_direction_x[ray] * data->player.direction_right_cos;
	data->ray.y = data->player.y;
	data->ray.x = data->player.x;
	*y = (int)data->ray.y;
	*x = (int)data->ray.x;
}

void	update_y_coordinate_and_wall_hit(t_data *data, int *y)
{
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

void	update_x_coordinate_and_wall_hit(t_data *data, int *x)
{
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

void	move_ray(t_data *data, int *y, int *x)
{
	if (data->ray.next_y_grid_distance < data->ray.next_x_grid_distance)
	{
		data->ray.y += data->ray.next_y_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_y_grid_distance * data->ray.x_vector;
		update_y_coordinate_and_wall_hit(data, y);
	}
	else
	{
		data->ray.y += data->ray.next_x_grid_distance * data->ray.y_vector;
		data->ray.x += data->ray.next_x_grid_distance * data->ray.x_vector;
		update_x_coordinate_and_wall_hit(data, x);
	}
}

void	calculate_next_grid_distance(t_data *data, int *y, int *x)
{
	if (data->ray.y_vector == 0)
		data->ray.next_y_grid_distance = 9999;
	else if (data->ray.y_vector > 0)
		data->ray.next_y_grid_distance
			= ((*y) + 1 - data->ray.y) / data->ray.y_vector;
	else
		data->ray.next_y_grid_distance
			= (data->ray.y - (*y)) / (-data->ray.y_vector);
	if (data->ray.x_vector == 0)
		data->ray.next_x_grid_distance = 9999;
	else if (data->ray.x_vector > 0)
		data->ray.next_x_grid_distance
			= ((*x) + 1 - data->ray.x) / data->ray.x_vector;
	else
		data->ray.next_x_grid_distance
			= (data->ray.x - (*x)) / (-data->ray.x_vector);
	move_ray(data, y, x);
}

double	get_perp_wall_dist(t_data *data)
{
	const double	delta_x = data->ray.x - data->player.x;
	const double	delta_y = data->ray.y - data->player.y;

	return (delta_x * data->player.direction_cos
		+ delta_y * data->player.direction_sin);
}

int	get_texture_x(t_data *data, const double perp_wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (data->ray.wall_hit == EAST || data->ray.wall_hit == WEST)
		wall_x = data->player.y + perp_wall_dist * data->ray.y_vector;
	else
		wall_x = data->player.x + perp_wall_dist * data->ray.x_vector;

	if (wall_x < 0)
		wall_x *= -1;
	wall_x = wall_x - (int)wall_x;

	tex_x = (int)(wall_x * data->textures[data->ray.wall_hit].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->textures[data->ray.wall_hit].width)
		tex_x = data->textures[data->ray.wall_hit].width - 1;

	return (tex_x * data->textures[data->ray.wall_hit].bytes_per_pixel);
}

int	get_texture_y(t_data *data, const int y, const int wall_height)
{
	const int	d = y * 256 - WINDOW_HEIGHT * 128 + wall_height * 128;
	int			tex_y;

	tex_y = ((d * data->textures[data->ray.wall_hit].height) / wall_height) / 256; //signed integer overflow

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= data->textures[data->ray.wall_hit].height)
		tex_y = data->textures[data->ray.wall_hit].height - 1;

	return (tex_y * data->textures[data->ray.wall_hit].size_line);
}

int	get_wall_start(const int wall_height)
{
	int	wall_start;

	wall_start = (WINDOW_HEIGHT - wall_height) / 2;
	if (wall_start < 0)
		wall_start = 0;
	return (wall_start);
}

int	get_wall_end(const int wall_start, const int wall_height)
{
	int	wall_end;

	wall_end = wall_start + wall_height;
	if (wall_end >= WINDOW_HEIGHT || wall_end < 0)
		wall_end = WINDOW_HEIGHT;
	return (wall_end);
}

int	get_texture_color(t_data *data,
	const int y, const int wall_height, const int tex_x)
{
	const char	*pixel_index = data->textures[data->ray.wall_hit].address
		+ get_texture_y(data, y, wall_height) + tex_x;
	const int	color = *(int *)pixel_index;

	return (color);
}

void	print_3d_ray(t_data *data, int ray, const double perp_wall_dist) //better name
{
	const double	wall_height = data->value.proj_plane / perp_wall_dist;
	const int		wall_start = get_wall_start(wall_height);
	const int		wall_end = get_wall_end(wall_start, wall_height);
	const int		tex_x = get_texture_x(data, perp_wall_dist);
	int				y;

	y = 0;
	while (y < wall_start)
	{
		fill_image_buffer(data->image, y, ray, data->surface[CEILING]);
		y++;
	}
	while (y < wall_end)
	{
		fill_image_buffer(data->image, y, ray,
			get_texture_color(data, y, wall_height, tex_x));
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		fill_image_buffer(data->image, y, ray, data->surface[FLOOR]);
		y++;
	}
}

void	calculate_raycasting_values(t_data *data)
{
	data->player.direction_sin = sin(data->player.direction_in_radians);
	data->player.direction_cos = cos(data->player.direction_in_radians);
	data->player.direction_right_sin
		= sin((data->player.direction + 90) * PI_180);
	data->player.direction_right_cos
		= cos((data->player.direction + 90) * PI_180);
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
		while (!is_wall(data, y, x)) //!is_wall()???
		{
			calculate_next_grid_distance(data, &y, &x);
			if (data->minimap_toggle && data->ray_toggle)
				fill_image_buffer(data->minimap, data->minimap.half_height
					+ (int)((data->ray.y - data->player.y)
						* data->value.scaled_grid_size),
					data->minimap.half_width
					+ (int)((data->ray.x - data->player.x)
						* data->value.scaled_grid_size), COLOR_RAY);
		}
		if (data->minimap_toggle && !data->ray_toggle)
			draw_minimap_ray(data);
		print_3d_ray(data, ray, get_perp_wall_dist(data));
		ray++;
	}
}

void	draw_crosshair(t_data *data)
{
	int	y;
	int	x;

	y = -2;
	while (++y < 1)
	{
		x = -6;
		while (++x < 5)
		{
			fill_image_buffer(data->image, data->image.half_height + y,
				data->image.half_width + x, COLOR_CROSSHAIR);
		}
	}
	x = -2;
	while (++x < 1)
	{
		y = -6;
		while (++y < 5)
		{
			fill_image_buffer(data->image, data->image.half_height + y,
				data->image.half_width + x, COLOR_CROSSHAIR);
		}
	}
}

void	render_game(t_data *data)
{
	if (data->minimap_toggle)
		draw_minimap_grid(data);
	raycasting(data);
	if (data->minimap_toggle)
		copy_minimap_to_image(data);
	draw_crosshair(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.buffer, 0, 0);
	data->movement_happend = false;
}

bool	is_wall(const t_data *data, double y, double x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width
		|| data->map.map[(int)y][(int)x] == '1'
		|| data->map.map[(int)y][(int)x] == ' ') //data->map.map[(int)y][(int)x] != '0' (keep in mind doors in bonus)
		return (true);
	return (false);
}

/* int	game_loop(t_data *data)
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
			turn_left(data, 150 * data->delta_time);
		if (data->keys['l'] && !data->keys['j'])
			turn_right(data, 150 * data->delta_time);
		if (data->keys['a'] && !data->keys['d'])
			move_left(data);
		if (data->keys['d'] && !data->keys['a'])
			move_right(data);
		if (data->keys['w'] && !data->keys['s'])
			move_forward(data);
		if (data->keys['s'] && !data->keys['w'])
			move_backwards(data);
		//if (data->movement_happend || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed
		render_game(data);
		//counter++;
	//}

	char fps_text[32];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.0f", current_fps);  // %.0f removes decimals
    mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, fps_text);
	return (0);
} */

int	game_loop(t_data *data)
{
	long	current_time;

	//if (get_current_time() - data->time_reference > 1000 / FPS)
	//{
		current_time = get_current_time();
		data->delta_time = (current_time - data->time_reference) / 1000.0;
		data->time_reference = current_time;
		if (data->keys['j'] && !data->keys['l'])
			turn_left(data, 150 * data->delta_time);
		if (data->keys['l'] && !data->keys['j'])
			turn_right(data, 150 * data->delta_time);
		if (data->keys['a'] && !data->keys['d'])
			move_left(data);
		if (data->keys['d'] && !data->keys['a'])
			move_right(data);
		if (data->keys['w'] && !data->keys['s'])
			move_forward(data);
		if (data->keys['s'] && !data->keys['w'])
			move_backwards(data);
		//if (data->movement_happend || data->keys['m']|| data->keys['r']) //if performance is fine without it, then not needed
		render_game(data);
	//}
	return (0);
}

void	start_mlx(t_data *data)
{
	//msg
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

void	call_mlx_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_click, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win, 17, 0L, exit_cub3d, NULL);
	mlx_loop_hook(data->mlx, game_loop, data);
}

int main(int argc, char **argv)
{
	t_data	*data;
	
	init_data();
	data = get_data();
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_cub3d(NULL); //msg
	parsing(argc, argv, data);
	calculate_fixed_values(data);
	start_mlx(data);
	call_mlx_hooks(data);
	render_game(data);
	mlx_loop(data->mlx);
	return (0);
}
