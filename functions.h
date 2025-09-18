/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/18 16:37:09 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Execution */



/* Parsing */

void	parsing(int argc, char **argv, t_data *data);
void	arg_validation(int argc, char *argv);
void	get_map(int fd, size_t start, t_data *data);
size_t	get_map_size(int fd, t_data *data);

/* Helper */

int		exit_cub3d(char *error_msg); // maybe have this only for execution and have an own function for the rest
t_data	*get_data(void);
void	free_2d_array(char **array);
bool	is_whitespace(char c);


#endif // FUNCTIONS_H