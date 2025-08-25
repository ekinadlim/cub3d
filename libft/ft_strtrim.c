/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:58:01 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/12 11:24:44 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_char(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_s;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	while (ft_check_char((char)s1[i], (char *)set) == 0)
		i++;
	while (ft_check_char((char)s1[j - 1], (char *)set) == 0)
		j--;
	trim_s = ft_substr(s1, i, j - i);
	if (trim_s == 0)
		return (0);
	return (trim_s);
}

/*int main()
{
	printf("%s\n", ft_strtrim("  Hello World  ", " "));
	printf("...");
}*/
