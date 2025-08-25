/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:41:34 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/06 20:09:03 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	sl;
	unsigned int	i;

	sl = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (sl);
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (sl);
}

/*#include <bsd/string.h>

int main()
{
	char s[] = "BadWorld";
	char d[] = "Hello";
	printf("%s\n", s);
	printf("%s\n", d);
	printf("%zu\n", ft_strlcpy(d, s, 1));
	printf("%s\n", s);
    printf("%s\n", d);
	printf("\n");
	char src[] = "BadWorld";
    char dst[] = "Hello";
	printf("%s\n", src);
    printf("%s\n", dst);
    printf("%zu\n", strlcpy(dst, src, 1));
	printf("%s\n", src);
    printf("%s\n", dst);
}*/
