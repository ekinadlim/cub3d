/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/02 14:15:54 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Execution */

int	exit_cub3d(char *error_msg);


/* Parsing */

void	parsing(int argc, char **argv, t_data *data);
void	arg_validation(int argc, char *argv);

/* Helper */

int		exit_cub3d(char *error_msg);
t_data	*get_data(void);


#endif // FUNCTIONS_H