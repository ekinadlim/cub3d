/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:16:18 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/18 19:57:02 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//had to use temp pointer because otherwise we will loose access to list
//because head moves and head should point to the first node
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

/*#include <stdio.h>
int main()
{
	t_list *head = NULL; // Initialize head of the list

    // Create nodes
    t_list *node1 = ft_lstnew((int *)10);
    t_list *node2 = ft_lstnew((int *)20);
    t_list *node3 = ft_lstnew((int *)30);
    t_list *node4 = ft_lstnew((int *)40);

    // Add nodes to the front of the list
    //ft_lstadd_front(&head, node1); // List: 10
    //ft_lstadd_front(&head, node2); // List: 20 -> 10
    //ft_lstadd_front(&head, node3); // List: 30 -> 20 -> 10
    	head = node1;
	node1->next = node2;
	node2->next = node3;
	ft_lstadd_front(&head, node4);
	
	int i = 0;
	t_list *hello = head;
	while (i < ft_lstsize(head))
	{
		printf("%d\n", (int *)hello->content);
		hello = hello->next;
		i++;
	}
	//printf("%d\n", head->content);
	//printf("%d\n", hello->content);
}*/
