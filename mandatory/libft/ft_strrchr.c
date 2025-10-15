/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:08:41 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/07 21:26:17 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len != -1)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}

/*int main()
{
    char *s = "HellotWorld";
    printf("%s\n", ft_strrchr("Hello", 108));
    printf("%s\n", strrchr("Hello", 108));
    
    printf("%p\n", ft_strrchr("Hello\0World", '\0'));
    printf("%p\n", strrchr("Hello\0World", '\0'));
    
    printf("%s\n", ft_strrchr(s,'t' + 256));
    printf("%s\n", strrchr(s,'t' + 256));
    
    int c = 't' + 256;
    int ct = 116 + 256;
    int ct2 = 116 + 256 + 256;
    printf("%c\n", c);
    printf("%c\n", ct);
    printf("%c\n", ct2);
}*/
