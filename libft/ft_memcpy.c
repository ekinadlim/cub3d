/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:31:16 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/10 15:07:19 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*dp;
	char			*sp;
	unsigned int	i;

	if (dest == 0 && src == 0)
		return (0);
	dp = dest;
	sp = (char *)src;
	i = 0;
	while (i < n)
	{
		dp[i] = sp[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	char dest[] = "okidoki";
	char src[] = "World Test123";
	printf("%s\n", dest);
	printf("%s\n", src);
	ft_memcpy(dest, src, 3);
	printf("%s\n", dest);
    printf("%s\n", src);

	printf("\n");
	char dest2[] = "okidoki";
    char src2[] = "World Test123";
    printf("%s\n", dest2);
    printf("%s\n", src2);
    memcpy(dest2, src2, 3);
    printf("%s\n", dest2);
    printf("%s\n", src2);
}*/
