/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:25:58 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/30 11:22:38 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printhex(unsigned long n, char up_low, int *count)
{
	if (n >= 16)
		ft_printhex(n / 16, up_low, count);
	if (up_low == 'X')
		ft_printchar("0123456789ABCDEF"[n % 16], count);
	else
		ft_printchar("0123456789abcdef"[n % 16], count);
}

void	ft_printptr(unsigned long n, char previous, int *count)
{
	if (n == 0)
	{
		ft_printstr("(nil)", count);
		return ;
	}
	else
	{
		if (previous == ' ')
			ft_printchar(' ', count);
		ft_printstr("0x", count);
		ft_printhex(n, 'x', count);
	}
}
