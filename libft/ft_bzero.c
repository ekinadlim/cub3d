/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:07:35 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/05 18:25:11 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	unsigned int	i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

/*int main()
{
	int i = 0;
	char s[] = "Hello";
	char str[] = "Hello";
	ft_bzero(s + 2, 10);
	bzero(str + 2, 10);
	while (i < 5)
	{
		printf("%d: %c\n", i, s[i]);
		printf("%d: %c\n", i, str[i]);
		i++;
	}
}*/
