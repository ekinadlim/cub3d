/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 15:38:29 by eadlim           ###   ########.fr       */
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
void	move_backwards(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	move_y(t_data *data, double y);
void	move_x(t_data *data, double x);

/* Player Rotation */

void	turn_right(t_data *data, double speed);
void	turn_left(t_data *data, double speed);

/* Minimap */

void	copy_minimap_to_image(t_data *data);
void	draw_minimap_ray(t_data *data);
void	draw_minimap_grid(t_data *data);

/* Raycasting */

void	raycasting(t_data *data);

/* Rendering */

void	draw_vertical_line(t_data *data, int ray, const double perp_wall_dist);
void	draw_crosshair(t_data *data);

/* Init Stuff */

void	init_data(void);
void	calculate_fixed_values(t_data *data);
void	start_mlx(t_data *data);

/* Game Loop */

int		game_loop(t_data *data);

/* ----------- Parsing ----------- */

void	parsing(int argc, char **argv, t_data *data);
void	arg_validation(int argc, char *argv);
void	get_map(size_t start, t_data *data);
size_t	get_map_size(t_data *data);
size_t	get_color(int surface, int filemask, t_data *data);
int		get_image(int direction, int filemask, t_data *data);
void	get_player(char **map, t_data *data);
void	floodfill(t_vec_2d_int pos, char **map, t_data *data);
void	check_map(char **map, t_data *data);

/* Helper */

t_data	*get_data(void);
long	get_current_time(void);
bool	is_whitespace(char c);
bool	is_wall(const t_data *data, double y, double x);
void	fill_image_buffer(t_image image, int y, int x, int color);

/* Cleanup */

void	exit_pars(char *err_msg, t_data *data);
int		exit_cub3d(char *error_msg);

#endif // FUNCTIONS_H