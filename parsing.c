/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:29:14 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 18:29:02 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parsing(int argc, char **argv, t_data *data)
{
	size_t	line_count;

	arg_validation(argc, argv[1]);
	data->pars.fd = open(argv[1], O_RDONLY);
	if (data->pars.fd < 0)
		exit_pars("Failed to open file!", data);
	line_count = get_elements(data);
	get_map_size(data);
	if (data->player.x == 0 || data->player.y == 0)
		exit_pars("Player is missing!", data);
	close(data->pars.fd);
	data->pars.fd = open(argv[1], O_RDONLY);
	if (data->pars.fd < 0)
		exit_pars("Failed to open file!", data);
	get_map(line_count, data);
	check_map(data->map.map, data);
	close(data->pars.fd);
}
