/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/08/29 14:30:30 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	map_name_validation(char *path, char *extension)
{
	int	path_index;
	int	ext_index;

	path_index = ft_strlen(path) - 1;
	ext_index = 3;
	while (path[path_index])
	{
		/* code */
	}
	
}

void	arg_validation(int argc, char **argv)
{
	if (argc < 2)
		exit_cub3d("Missing Argument!");
	else if (argc > 2)
		exit_cub3d("Only 1 Argument required!");
	map_name_validation(argv[1], ".cub");
}

void	parsing(int argc, char **argv, t_data *data)
{
	(void)data;
	
}
