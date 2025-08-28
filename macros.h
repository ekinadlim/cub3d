/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:13:57 by eadlim            #+#    #+#             */
/*   Updated: 2025/08/28 21:13:55 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define _GNU_SOURCE //for M_PI

# define WINDOW_HEIGHT	720 //480
# define WINDOW_WIDTH	1280 //640

# define MINIMAP_HEIGHT	100
# define MINIMAP_WIDTH	100
# define MINIMAP_POS_Y	0//(WINDOW_HEIGHT - MINIMAP_HEIGHT) /* BOTTOM */
# define MINIMAP_POY_X	0//(WINDOW_WIDTH - MINIMAP_WIDTH) /* RIGHT */
# define TILE_SIZE		10

# define FPS	60
# define FOV	90

# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_LEFT	65361

#endif // MACROS_H