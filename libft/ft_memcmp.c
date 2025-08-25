/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:30:12 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/07 19:40:34 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;
	unsigned int	i;

	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (sp1[i] != sp2[i])
			return (sp1[i] - sp2[i]);
		i++;
	}
	return (0);
}

/*int main()
{
    const char s1[] = "Hello";
    const char s2[] = "Hella";
    char s3[] = "Hello";
    char s4[] = "Hella";

    printf("%d\n", ft_memcmp(s1, s2, 8));
    printf("%d\n\n", memcmp(s1, s2, 8));

    printf("%d\n", ft_memcmp(s3, s4, 8));
    printf("%d\n\n", memcmp(s3, s4, 8));

    printf("%d\n", ft_memcmp("Hello", "Hella", 8));
    printf("%d\n", memcmp("Hello", "Hella", 8));
}*/
