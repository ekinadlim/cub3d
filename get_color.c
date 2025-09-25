/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:03:43 by eadlim            #+#    #+#             */
/*   Updated: 2025/09/25 15:49:24 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	comma_handling(int color_shift, char str_num[5], char *line, t_data *data)
{
	if (color_shift == 0)
		exit_pars("Remove the comma!", line, data);
	if (!str_num[0])
		exit_pars("Missing number for color code!", line, data);
	return (ft_atoi(str_num));
}

int	get_color_number(char *line, size_t *i, int color_shift, t_data *data)
{
	char	str_num[5];
	size_t	digit;

	digit = 0;
	ft_bzero(str_num, 5);
	while (line[*i])
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			if (digit > 2 || (digit > 0 && ((str_num[0] == '0' && str_num[digit - 1] == '0') || is_whitespace(line[*i - 1]))))
				exit_pars("Invalid Color Code!", line, data);
			str_num[digit++] = line[*i];
		}
		else if (line[*i] == ',')
		{
			(*i)++;
			return (comma_handling(color_shift, str_num, line, data));
		}
		else if (!is_whitespace(line[*i]))
			exit_pars("Garbage in Surface element!", line, data);
		(*i)++;
	}
	return (ft_atoi(str_num));
}

size_t	get_color(int surface, char *line, t_data *data)
{
	int		one_color;
	int		color_shift;
	size_t	i;

	color_shift = 2;
	i = 1;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (i == 1)
			exit_pars("Wrong Surface Format!", line, data);
		one_color = get_color_number(line, &i, color_shift, data);
		if (one_color < 0 || one_color > 255)
			exit_pars("Wrong color values!", line, data);
		data->surface[surface] += one_color << (8 * color_shift);
		color_shift--;
		if (color_shift < -1)
			exit_pars("Too many color values!", line, data);
	}
	if (color_shift != -1)
		exit_pars("Invalid amount of colors!", line, data);
	return (1 << (surface + 4));
}
