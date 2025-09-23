/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:15:06 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/23 12:44:05 by eadlim           ###   ########.fr       */
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
size_t	get_color(int surface, char *line, t_data *data);
int		get_image(int direction, char *line, t_data *data);
void	get_player(char **map, t_data *data);
void	floodfill(int x, int y, char **map, t_data *data);
void	exit_pars(char *err_msg, char *line, t_data *data);

/* Helper */

int	exit_cub3d(char *error_msg); // maybe have this only for execution and have an own function for the rest
t_data	*get_data(void);
void	free_2d_array(char **array);
bool	is_whitespace(char c);

#endif // FUNCTIONS_H