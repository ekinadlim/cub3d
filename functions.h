/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/01 16:10:07 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Execution */

int	exit_cub3d(char *error_msg);


/* Parsing */

void	parsing(int argc, char **argv, t_data *data);

/* Helper */

int		exit_cub3d(char *error_msg);
t_data	*get_data(void);


#endif // FUNCTIONS_H