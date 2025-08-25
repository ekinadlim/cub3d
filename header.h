#ifndef HEADER_H
# define HEADER_H

# define _GNU_SOURCE //for M_PI

# include "libft/libft.h"
# include "mlx.h"
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>

#include <stdio.h> //remove

# define WINDOW_HEIGHT	500 //480
# define WINDOW_WIDTH	500 //640

# define FPS	60
# define FOV	90

# define TILE_SIZE	50

# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_LEFT	65361

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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_player	player;
	t_image		image;
	t_ray		ray;
	bool		keys[256];
	long		time_reference;
	char		**map;
}	t_data;

#endif
