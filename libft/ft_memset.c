/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:19:01 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/06 20:58:46 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*p;
	unsigned int	i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}

/*int main()
{
	char s[] = "What is going on? Help!";
	char *str = s;
	int a[] = {1, 2, 3, 4, 5};
	int arr[] = {1, 2, 3, 4, 5};
	int	c = 65;
	size_t n = 16;
	int i = 0;

	ft_memset(s, c, n);
	printf("%s\n", s);
	memset(str, c, n);
    printf("%s\n", str);

	while (i < 5)
    {
        printf("%d", a[i]);
		i++;
	}
	printf("\n");
	i = 0;
	ft_memset(a, 0, 17);
	while (i < 5)
    {
        printf("%d", a[i]);
        i++;
    }
	printf("\n");
	i = 0;
	while (i < 5)
    {
        printf("%d", arr[i]);
        i++;
    }
	printf("\n");
	i = 0;
	memset(arr, 0, 5);
	while (i < 5)
	{
    	printf("%d", arr[i]);
		i++;
	}
}*/
