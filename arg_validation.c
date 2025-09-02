/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:14:46 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/02 14:16:31 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	map_name_validation(char *path, char *extension)
{
	int	path_index;
	int	ext_index;

	if (!path)
		exit_cub3d("File Path missing!");
	path_index = ft_strlen(path) - 1;
	ext_index = 3;
	while (extension[ext_index])
	{
		if (path_index <= 0 || path[path_index] != extension[ext_index])
			exit_cub3d("Wrong file format!");
		path_index--;
		ext_index--;
	}
	if (path[path_index] == '/')
		exit_cub3d("Wrong file name!");
}

void	arg_validation(int argc, char *argv)
{
	if (argc < 2)
		exit_cub3d("Missing Argument!");
	else if (argc > 2)
		exit_cub3d("Only 1 Argument required!");
	map_name_validation(argv, ".cub");
}
