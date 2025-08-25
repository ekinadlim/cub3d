/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:47:53 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/17 13:27:35 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//0/0 would cause undefined behavior
//check for overflow, if nmemb * size = SIZE_MAX + 2 then result wraps
//around so it's 1
//if (size == 0 || nmemb == 0) return (0);
//same as malloc(0), both can be safely passed to free()
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	if (nmemb != 0 && (nmemb * size) / nmemb != size)
		return (0);
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (0);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

/*int main()
{
	int i = 0;
	char *s1 = ft_calloc(2, 0);
	while (i < 1)
	{
		printf("%d, ", s1[i]);
		i++;
	}
	printf("\n");
	char *s2 = ft_calloc(0, 2);
	while (i < 2)
	{
		printf("%d, ", s2[i]);
		i++;
	}
	//size_t ok = 18446744073709551615;
	//printf("%zu", ok);
}*/
