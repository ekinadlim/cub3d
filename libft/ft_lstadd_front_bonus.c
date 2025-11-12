/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/18 17:34:51 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == 0)
		return ;
	new->next = *lst;
	*lst = new;
}

/*// Function to print the linked list
void ft_lstprint(t_list *lst) {
    while (lst != NULL) {
        printf("%d -> ", lst->content); // Print the data
        lst = lst->next;              // Move to the next node
    }
    printf("NULL\n"); // Indicate the end of the list
}

int main() {
    t_list *head = NULL; // Initialize head of the list

    // Create nodes
    t_list *node1 = ft_lstnew(10);
    t_list *node2 = ft_lstnew(20);
    t_list *node3 = ft_lstnew(30);
    t_list *node4 = ft_lstnew(15);

    // Add nodes to the front of the list
    ft_lstadd_front(&head, node1); // List: 10
    ft_lstadd_front(&head, node2); // List: 20 -> 10
    ft_lstadd_front(&head, node3); // List: 30 -> 20 -> 10

    // Print the linked list
    ft_lstprint(head);
    ft_lstprint(head);

    return 0;
}*/
