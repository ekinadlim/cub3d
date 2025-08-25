/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:41:43 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/07 20:29:24 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (little[i] == 0 || big == little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && i + j < len)
			j++;
		if (little[j] == 0)
			return ((char *)big + i);
		i++;
	}
	return (0);
}
//fixed just by adding big[i + j] in 2nd while loop
//(so it doesn't read passed big)
/*#include <bsd/string.h>

int main()
{
	printf("%s\n", ft_strnstr("testoktest", "ok", -1));
	printf("%s\n", strnstr("testoktest", "ok", -1));
	
	printf("%s\n", ft_strnstr("1234abcd", "abcd", 9));
	printf("%s\n", strnstr("1234abcd", "abcd", 9));
}*/
