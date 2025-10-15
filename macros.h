/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:13:57 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/11 14:10:51 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define _GNU_SOURCE //for M_PI

/* ------------- CONSTANTS -------------- */

//Converts degrees to radians
# define PI_180 0.017453292519943295474371680598
//The smallest positive floating-point number
# define EPSILON 1e-10

# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_LEFT	65361

/* -------------- PARSING --------------- */

# define MAP_CHAR_SET	"01 NESW"
# define ELEMENT_COUNT	6
# define MAX_HEIGHT		5000
# define MAX_WIDTH		5000

/* -------------- DISPLAY --------------- */

# define WINDOW_WIDTH	1280 /* 1600 */ /* 640 */
# define WINDOW_HEIGHT	720 /* 900 */ /* 480 */

# define UNLIMITED	-1 //For FPS
# define FPS	UNLIMITED
# define FOV	90

/* -------------- MINI MAP--------------- */

# define MINIMAP_HEIGHT	100
# define MINIMAP_WIDTH	100
# define MINIMAP_POS_Y	0
# define MINIMAP_POS_X	0
//How many Grids there are per row/column on the Minimap
# define GRID_COUNT		10
//How many Pixels there are per row/column for each Grid
# define GRID_SIZE		10
//For the Minimap size
# define SCALING		1.5

# define COLOR_PLAYER	0xFF0000    //Red
# define COLOR_RAY		0xFFDD44    //Yellow
# define COLOR_VOID		0x000000    //Black
# define COLOR_WALL		0x666666    //Medium gray
# define COLOR_FLOOR	0x333333    //Dark gray

/* -------------- KEY BINDS ------------- */

# define MOVE_FORWARD 'w'
# define MOVE_BACK 's'
# define MOVE_RIGHT 'd'
# define MOVE_LEFT 'a'

/* -------------- CROSSHAIR ------------- */

# define COLOR_CROSSHAIR	0xFFFFFF

/* ---------------- SPEED --------------- */

# define MOVEMENT_SPEED		4
# define TURN_SPEED			150
# define MOUSE_SENSITIVITY	0.1

typedef enum e_cardinal_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_cardinal_direction;

typedef enum e_color
{
	FLOOR,
	CEILING
}	t_color;

#endif // MACROS_H
