/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:19 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/02 14:46:31 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// x and y axis for int
typedef struct s_vec_2d_int
{
	int			x;
	int			y;
}				t_vec_2d_int;

// x and y axis for size_t
typedef struct s_vec_2d_size_t
{
	size_t		x;
	size_t		y;
}				t_vec_2d_size_t;

typedef struct s_player
{
	double		y;
	double		x;
	double		direction;
	double		direction_in_radians; //data->player.direction * M_PI / 180.0
	double		direction_sin; //sin(data->player.direction * M_PI / 180.0)
	double		direction_cos; //cos(data->player.direction * M_PI / 180.0)
	double		direction_right_sin; //sin((data->player.direction + 90) * M_PI / 180.0)
	double		direction_right_cos; //cos((data->player.direction + 90) * M_PI / 180.0)
}				t_player;

typedef struct s_value //better name
{
	double		proj_plane; //(WINDOW_WIDTH / 2.0) / tan((FOV * PI_180) / 2.0)
	double		ray_direction_x[WINDOW_WIDTH];
	double		scaled_grid_size; //GRID_SIZE * SCALING
}				t_value;

typedef struct s_image
{
	int			height;
	int			width;
	int			half_height;
	int			half_width;
	void		*buffer;
	char		*address;
	int			bytes_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_ray
{
	double		y_vector;
	double		x_vector;
	double		y;
	double		x;
	double		next_y_grid_distance;
	double		next_x_grid_distance;
	int			wall_hit;
}				t_ray;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}				t_map;

typedef	struct s_parsing
{
	int			fd;
	char		*line;
}				t_parsing;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_image		image;
	t_image		minimap;
	bool 		movement_happend; // to know if we need to print (better name)
	bool		minimap_toggle; //on/off
	bool		ray_toggle; //which ray view in minimap
	t_ray		ray;
	bool		keys[256];
	long		time_reference;
	double		delta_time;
	t_map		map;
	int			surface[2];
	t_image		textures[4];
	t_parsing	pars;
	t_value		value;
}				t_data;

#endif // STRUCTURES_H