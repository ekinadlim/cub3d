/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:15:00 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/18 16:38:24 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}

/*#include <stdio.h>

int main()
{
	int i = 0;
	char *str = "Hello";
	t_list *hi = ft_lstnew(str);
	printf("%s\n", (char *)hi->content);
	while (str[i])
	{
		printf("%c\n", str[i]);
		i++;
	}
}*/
