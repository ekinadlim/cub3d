/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:19 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/23 12:48:05 by eadlim           ###   ########.fr       */
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
	size_t	x;
	size_t	y;
}			t_vec_2d_size_t;

typedef struct s_player
{
	double		y;
	double		x;
	double		direction;
}				t_player;

typedef struct s_image
{
	int			height;
	int			width;
	void		*buffer;
	char		*address;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_ray
{
	double		direction;
	double radian; // better name?
	double		y_vector;
	double		x_vector;
	double		y;
	double		x;
	// double	step;
	// bool	hit_wall;
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
	int			fd;
}				t_data;

#endif // STRUCTURES_H