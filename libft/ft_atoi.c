/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:29:53 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/08 18:12:39 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	minus;

	i = 0;
	result = 0;
	minus = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (10 * result) + nptr[i] - '0';
		i++;
	}
	if (minus == 1)
		result = -result;
	return (result);
}

/*#include <stdlib.h>

int main()
{
	printf("%d\n", ft_atoi("  -0102b34"));
	printf("%d\n", atoi("  -0102b34"));
}*/
