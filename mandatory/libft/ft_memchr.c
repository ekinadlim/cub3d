/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:43:15 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/07 19:07:37 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;
	unsigned int	i;

	sp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (sp[i] == (unsigned char)c)
			return (sp + i);
		i++;
	}
	return (0);
}

/*int main()
{
	const char *s = "Hello";
	const char *prints = ft_memchr(s, 108, 3);
	printf("%s\n", prints);
	
	const char *s2 = "Hello";
	const char *prints2 = ft_memchr(s, 108, 3);
    	printf("%s\n", prints2);
    	
    	const char *s3 = "Hello";
	const char *prints3 = ft_memchr("bonjourno", 'n', 2);
    	printf("%s\n", prints3);
}*/
