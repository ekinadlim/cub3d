/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:33:46 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/11 20:35:05 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	s_len;
	unsigned int	sub_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		sub = (char *)malloc(1);
		if (sub == 0)
			return (0);
		sub[0] = '\0';
		return (sub);
	}
	sub_len = ft_strlen(s + start);
	if (len > sub_len)
		len = sub_len;
	sub = (char *)malloc(len + 1);
	if (sub == 0)
		return (0);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

/*int main()
{
	printf("%s\n", ft_substr(0, 0, 10));
}*/
