/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:14:46 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/30 14:21:46 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	map_name_validation(char *path, char *extension)
{
	int	path_index;
	int	ext_index;

	if (!path)
		exit_pars("File Path missing!", NULL);
	path_index = ft_strlen(path) - 1;
	ext_index = 3;
	while (extension[ext_index])
	{
		if (path_index <= 0 || path[path_index] != extension[ext_index])
			exit_pars("Wrong file format!", NULL);
		path_index--;
		ext_index--;
	}
	if (path[path_index] == '/')
		exit_pars("Wrong file name!", NULL);
}

void	arg_validation(int argc, char *argv)
{
	if (argc < 2)
		exit_pars("Missing Argument!", NULL);
	else if (argc > 2)
		exit_pars("Only 1 Argument required!", NULL);
	map_name_validation(argv, ".cub");
}
