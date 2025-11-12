/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eadlim <eadlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:03:43 by eadlim            #+#    #+#             */
/*   Updated: 2025/10/24 16:15:01 by eadlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	comma_handling(int color_shift, char str_num[5], t_data *data)
{
	if (color_shift == 0)
		exit_pars("Remove the comma!", data);
	if (!str_num[0])
		exit_pars("Missing number for color code!", data);
	return (ft_atoi(str_num));
}

static int	get_color_number(size_t *i, int color_shift, t_data *data)
{
	char	str_num[5];
	size_t	digit;

	digit = 0;
	ft_bzero(str_num, 5);
	while (data->pars.line[*i])
	{
		if (data->pars.line[*i] >= '0' && data->pars.line[*i] <= '9')
		{
			if ((digit > 0 && ((str_num[0] == '0' && str_num[digit - 1] == '0')
						|| is_whitespace(data->pars.line[*i - 1])))
				|| digit > 2)
				exit_pars("Invalid Color Code!", data);
			str_num[digit++] = data->pars.line[*i];
		}
		else if (data->pars.line[*i] == ',')
		{
			(*i)++;
			return (comma_handling(color_shift, str_num, data));
		}
		else if (!is_whitespace(data->pars.line[*i]))
			exit_pars("Garbage in Surface element!", data);
		(*i)++;
	}
	return (ft_atoi(str_num));
}

size_t	get_color(int surface, t_data *data)
{
	int		one_color;
	int		color_shift;
	size_t	i;

	if ((1 << (surface + 4)) & data->filemask)
		exit_pars("Multiple occurance of the same element!", data);
	color_shift = 2;
	i = 1;
	while (data->pars.line[i])
	{
		while (data->pars.line[i] && is_whitespace(data->pars.line[i]))
			i++;
		if (i == 1)
			exit_pars("Wrong Surface Format!", data);
		one_color = get_color_number(&i, color_shift, data);
		if (one_color < 0 || one_color > 255)
			exit_pars("Wrong color values!", data);
		data->surface[surface] += one_color << (8 * color_shift);
		color_shift--;
		if (color_shift < -1)
			exit_pars("Too many color values!", data);
	}
	if (color_shift != -1)
		exit_pars("Invalid amount of colors!", data);
	return (1 << (surface + 4));
}
