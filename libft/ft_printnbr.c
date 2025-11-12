/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:25:11 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/29 18:56:30 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) += 11;
		return ;
	}
	else if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
		(*count)++;
	}
	if (n >= 10)
	{
		ft_printnbr(n / 10, count);
		ft_printnbr(n % 10, count);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
		(*count)++;
	}
}

void	ft_check_negative(int n, char previous, int *count)
{
	if (previous == ' ' && n >= 0)
		ft_printchar(' ', count);
	ft_printnbr(n, count);
}
