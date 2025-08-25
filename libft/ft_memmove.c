/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:44:09 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/17 13:23:41 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*dp;
	char			*sp;
	unsigned int	i;

	if (dest == 0 && src == 0)
		return (0);
	dp = dest;
	sp = (char *)src;
	i = 0;
	if (dest < src)
	{
		return (ft_memcpy(dest, src, n));
	}
	else
	{
		while (i < n)
		{
			dp[n - 1 - i] = sp[n - 1 - i];
			i++;
		}
	}
	return (dest);
}

/*int main()
{
    //char dest[] = "okidoki";
    char src[] = "World Test123";
    printf("dst: %s\n", src + 6);
    printf("src: %s\n", src);
    ft_memmove(src + 6, src, 8);
    //memmove(((void*)0), ((void*)0), 3);
    printf("dst: %s\n", src + 6);
    printf("src: %s\n", src);

    printf("\n");
    //char dest2[] = "okidoki";
    char src2[] = "World Test123";
    printf("dst: %s\n", src2 + 6);
    printf("src: %s\n", src2);
    memmove(src2 + 6, src2, 8);
    //memmove(((void*)0), ((void*)0), 3);
    printf("dst: %s\n", src2 + 6);
    printf("src: %s\n", src2);
}*/
