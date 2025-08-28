/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:19 by eadlim            #+#    #+#             */
/*   Updated: 2025/08/28 17:53:27 by eadlim           ###   ########.fr       */
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
}	t_ray;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;

}	t_texture;

typedef struct s_color
{
	int	floor;
	int	ceiling;
}	t_color;

typedef struct s_input
{
	char	**map;
}			t_input;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_player	player;
	t_image		image;
	//t_image	minimap;
	t_ray		ray;
	bool		keys[256];
	long		time_reference;
	char		**map;
}	t_data;

#endif // STRUCTURES_H