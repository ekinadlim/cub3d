/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:59:04 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/07 21:26:38 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

/*int main()
{
	char *s = "HellotWorld";
	printf("%s\n", ft_strchr("Hello", 108));
	printf("%s\n", strchr("Hello", 108));
	
	printf("%p\n", ft_strchr("Hello",'\0'));
	printf("%p\n", strchr("Hello",'\0'));
	
	printf("%s\n", ft_strchr(s,('t' + 256)));
	printf("%s\n", strchr(s,('t' + 256)));
}*/
