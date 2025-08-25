/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:39:24 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/17 13:24:41 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ps1;
	char	*ps2;
	char	*new;
	int		ps1_len;
	int		ps2_len;

	ps1 = (char *)s1;
	ps2 = (char *)s2;
	ps1_len = ft_strlen(ps1);
	ps2_len = ft_strlen(ps2);
	new = (char *)malloc(ps1_len + ps2_len + 1);
	if (new == 0)
		return (0);
	ft_memcpy(new, ps1, ps1_len);
	ft_memcpy(new + ps1_len, ps2, ps2_len);
	new[ps1_len + ps2_len] = '\0';
	return (new);
}

/*int main()
{
	printf("%s\n", ft_strjoin("Hello", "World"));
}*/
