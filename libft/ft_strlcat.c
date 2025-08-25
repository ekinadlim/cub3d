/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:57:44 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/06 18:22:16 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dl;
	unsigned int	sl;
	unsigned int	i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = 0;
	if (dl >= size)
		sl = sl + size;
	else
		sl = sl + dl;
	while (src[i] && dl + 1 < size)
	{
		dst[dl] = src[i];
		dl++;
		i++;
	}
	dst[dl] = '\0';
	return (sl);
}

/*#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int	main(void)
{
	char	src[] = "hello i am armin";
	char	dest[20] = "world";
	unsigned int i = 2;
	printf("%zu\n", strlcat(dest, src, i));
	printf("%lu\n", sizeof(dest));
	printf("%s\n", dest);
	char    sr[] = "hello i am armin";
    char    des[20] = "world";
	printf("%zu\n", ft_strlcat(des, sr, i));
	printf("%lu\n", sizeof(des));
	printf("%s\n", des);
}*/
