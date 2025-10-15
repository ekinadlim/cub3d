/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:25:35 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/27 17:59:08 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printunbr(unsigned int n, int *count)
{
	char	c;

	if (n >= 10)
	{
		ft_printunbr(n / 10, count);
		ft_printunbr(n % 10, count);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
		(*count)++;
	}
}
