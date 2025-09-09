/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:19 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/09 15:24:34 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_player
{
	double	y;
	double	x;
	double	direction;
}	t_player;

typedef struct s_image
{
	int		height;
	int		width;
	void	*buffer;
	char	*address;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_ray
{
	double	direction;
	double	radian; //better name?
	double	y_vector;
	double	x_vector;
	double	y;
	double	x;
	//double	step;
	//bool	hit_wall;
	double	next_y_grid_distance;
	double	next_x_grid_distance;
	int		wall_hit;
}	t_ray;

/* typedef struct s_texture
{
	t_image	north; //adress needed so maybe just use t_image
	t_image	south;
	t_image	west;
	t_image	east;

}	t_texture;
 */

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_image		image;
	t_image		minimap;
	bool		movement_happend; //to know if we need to print
	bool		minimap_toggle;
	t_ray		ray;
	bool		keys[256];
	long		time_reference;
	double		delta_time;
	char		**map;
	int			surface[2];
	t_image		texture[4];
}	t_data;

#endif // STRUCTURES_H