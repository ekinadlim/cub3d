/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:44:54 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/16 16:58:06 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(int nb, int count)
{
	if (nb >= 10)
		count = ft_digit_count(nb / 10, count);
	count = count + 1;
	return (count);
}

static void	ft_putnbr(char *str, int *index, int n)
{
	if (n >= 10)
		ft_putnbr(str, index, n / 10);
	str[(*index)++] = n % 10 + '0';
}

static	void	*ft_int_min(char *str)
{
	str = (char *)malloc(12);
	if (str == 0)
		return (0);
	str = ft_memcpy(str, "-2147483648", 12);
	str[11] = '\0';
	return (str);
}

//had to initialize str because of -Werror
char	*ft_itoa(int n)
{
	char	*str;
	int		minus_and_index;

	if (n == -2147483648)
	{
		str = 0;
		return (ft_int_min(str));
	}
	minus_and_index = 0;
	if (n < 0)
	{
		minus_and_index = 1;
		n = -n;
	}
	str = (char *)malloc(ft_digit_count(n, 0) + minus_and_index + 1);
	if (str == 0)
		return (0);
	if (minus_and_index == 1)
		str[0] = '-';
	ft_putnbr(str, &minus_and_index, n);
	str[minus_and_index] = '\0';
	return (str);
}

/*int main()
{
	printf("%s\n", ft_itoa(-2147483648));
}*/
