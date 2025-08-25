/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:49:16 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/09 20:00:36 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (dup == 0)
		return (0);
	while (s[i])
	{
		dup[i] = (char)s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*int main()
{
	const char *s = "Hello";
	const char *s2 = "Hello";
	printf("%s\n", ft_strdup(s));
	printf("%s\n", strdup(s2));
}*/
