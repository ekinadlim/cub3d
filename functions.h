/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 18:34:03 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* ----------- Execution ----------- */

/* Input */

int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		mouse_click(int button, int x, int y, t_data *data);
int		mouse_release(int button, int x, int y, t_data *data);

/* Player Movement */

void	move_forward(t_data *data);
void	move_back(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	move_y(t_data *data, double y);
void	move_x(t_data *data, double x);

/* Player Rotation */

void	turn_right(t_data *data, double speed);
void	turn_left(t_data *data, double speed);

/* Minimap */

void	draw_minimap_grid(t_data *data);
void	draw_minimap_ray(t_data *data);

/* Raycasting */

void	raycasting(t_data *data);
void	calculate_next_grid_distance(t_data *data, int *y, int *x);

/* Rendering */

void	render_game(t_data *data);
void	draw_vertical_line(t_data *data, int ray, const double perp_wall_dist);
int		get_texture_x(t_data *data, const double perp_wall_dist);
int		get_wall_start(const int wall_height);
int		get_wall_end(const int wall_start, const int wall_height);
int		get_texture_color(t_data *data,
			const int y, const int wall_height, const int tex_x);

/* Doors */

void	y_doors(t_data *data, const double y, char door,
			bool (*is_door)(const t_data *, const double, const double));
void	x_doors(t_data *data, const double x, char door,
			bool (*is_door)(const t_data *, const double, const double));

/* Init Stuff */

void	init_data(void);
void	calculate_fixed_values(t_data *data);
void	start_mlx(t_data *data);
void	init_flashlight(t_data *data);

/* Game Loop */

int		game_loop(t_data *data);

/* ----------- Parsing ----------- */

void	parsing(int argc, char **argv, t_data *data);
void	arg_validation(int argc, char *argv);
size_t	get_elements(t_data *data);
void	get_map(size_t start, t_data *data);
void	get_map_size(t_data *data);
size_t	get_color(int surface, t_data *data);
int		get_images(int type, t_data *data);
void	get_player(int pos_x, int pos_y, char c, t_data *data);
void	check_map(char **map, t_data *data);

/* Helper */

t_data	*get_data(void);
long	get_current_time(void);
bool	is_whitespace(char c);
bool	is_wall(const t_data *data, const double y, const double x);
bool	is_closed_door(const t_data *data, const double y, const double x);
bool	is_open_door(const t_data *data, const double y, const double x);
void	fill_image_buffer(t_image image,
			const int y, const int x, int color);

/* Cleanup */

void	exit_pars(char *err_msg, t_data *data);
int		exit_cub3d(char *error_msg);

#endif // FUNCTIONS_H