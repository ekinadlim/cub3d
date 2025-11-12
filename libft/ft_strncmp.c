/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:24:45 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/09 12:43:16 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	
	printf("%d\n", ft_strncmp(s1, s2, 8));
    printf("%d\n\n", strncmp(s1, s2, 8));

	printf("%d\n", ft_strncmp(s3, s4, 8));
    printf("%d\n\n", strncmp(s3, s4, 8));

	printf("%d\n", ft_strncmp("Hello", "Hella", 8));
	printf("%d\n", strncmp("Hello", "Hella", 8));

	printf("%d\n", ft_strncmp("abcdef", "abc\375xx", 4));
	printf("%d\n", strncmp("abcdef", "abc\375xx", 4));
}*/
