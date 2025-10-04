/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:13:57 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 14:20:38 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define _GNU_SOURCE //for M_PI

# define MAP_CHAR_SET "01 NESW"

# define PI_180 0.017453292519943295474371680598 // converts degrees to radians
//Do a lot of similar MACROS

#define EPSILON 1e-10

# define WINDOW_WIDTH	/* 1600 */ 1280 /* 640 */
# define WINDOW_HEIGHT	/* 900 */ 720 /* 480 */

# define BUFFER_SIZE 100

# define ELEMENT_COUNT 6

# define MINIMAP_HEIGHT	100
# define MINIMAP_WIDTH	100
# define MINIMAP_POS_Y	0 //(WINDOW_HEIGHT - MINIMAP_HEIGHT) /* BOTTOM */
# define MINIMAP_POY_X	0 //(WINDOW_WIDTH - MINIMAP_WIDTH) /* RIGHT */
# define GRID_COUNT		10 //How many Grids there are per row/column on the Minimap
# define GRID_SIZE		10 //How many Pixels there are per row/column for each Grid
# define SCALING		1.5 //For the Minimap size

# define FPS	60
# define FOV	90

# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_LEFT	65361

// Minimap Colors
/* # define COLOR_PLAYER	0xFF0000
# define COLOR_RAY		0xFFFF00
# define COLOR_VOID		0x000000
# define COLOR_WALL		0x0001F4
# define COLOR_FLOOR	0x000064 */

# define COLOR_PLAYER	0xFF0000    // Red player (stands out)
# define COLOR_RAY		0xFFDD44    // Yellow rays (visible but not harsh)
# define COLOR_VOID		0x000000    // Dark void
# define COLOR_WALL		0x666666    // Medium gray walls
# define COLOR_FLOOR	0x333333    // Dark gray floor

# define COLOR_CROSSHAIR	0xFFFFFF

# define MOVEMENT_SPEED	4

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
