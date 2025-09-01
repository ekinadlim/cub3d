/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/01 16:15:02 by eadlim           ###   ########.fr       */
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

void	parsing(int argc, char **argv, t_data *data)
{
	(void)data;
	(void)argv;
	(void)argc;
}

int main(int argc, char *argv[])
{
	arg_validation(argc, argv[1]);
	ft_printf("Everything good!");
}
