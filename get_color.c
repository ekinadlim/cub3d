/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:03:43 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/20 15:45:55 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_color_number(char *line, size_t *i, int color_shift)
{
	char	str_num[5];
	size_t	digit;

	digit = 0;
	ft_bzero(str_num, 5);
	while (line[*i])
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			if (digit > 2)
				exit_cub3d("Invalid Color Code!");
			str_num[digit++] = line[*i];
		}
		else if (line[*i] == ',')
		{
			if (color_shift == 0)
				exit_cub3d("Remove the comma!");
			if (!str_num[0])
				exit_cub3d("Missing number for color code!");
			(*i)++;
			return (ft_atoi(str_num));
		}
		else if (line[*i] && !is_whitespace(line[*i]))
			exit_cub3d("Garbage in Surface element!");
		(*i)++;
	}
	return (ft_atoi(str_num));
}

size_t	get_color(t_data *data, char *line, int surface)
{
	int		full_color;
	int		one_color;
	int		color_shift;
	size_t	i;
	
	color_shift = 2;
	full_color = 0;
	i = 1;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (i == 1)
			return (free(line), exit_cub3d("Wrong Surface Format"), 0);
		one_color = get_color_number(line, &i, color_shift);
		if (one_color < 0 || one_color > 255 )
			exit_cub3d("Wrong color values!");
		full_color += one_color << (8 * color_shift);
		color_shift--;
		if (color_shift < -1)
			exit_cub3d("Too many color values!");
	}
	if (color_shift != -1)
		exit_cub3d("Invalid amount of colors!");
	data->surface[surface] = full_color;
	return (1 << (surface + 4));
}
