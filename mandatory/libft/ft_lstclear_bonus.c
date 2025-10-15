/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:38:57 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/18 20:39:49 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//need to keep track of temp->next so after we freewe can
//still use temp->next that's why we need right to store temp->next
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*right;

	if (lst == 0 || del == 0)
		return ;
	temp = *lst;
	while (temp)
	{
		right = temp->next;
		del(temp->content);
		free (temp);
		temp = right;
	}
	*lst = 0;
}
/*#include <stdio.h>
#include <string.h>
void del_content(void *content) {
    free(content);  // Free the dynamically allocated content
}
int main() {
    // Create a simple list with dynamically allocated strings
    t_list *node1 = ft_lstnew(strdup("Node 1"));
    t_list *node2 = ft_lstnew(strdup("Node 2"));
    t_list *node3 = ft_lstnew(strdup("Node 3"));

    // Link the nodes
    node1->next = node2;
    node2->next = node3;

    // Print the content of the list before deletion
    printf("Before deletion:\n");
    printf("Node1 content: %s\n", (char *)node1->content);
    printf("Node2 content: %s\n", (char *)node2->content);
    printf("Node3 content: %s\n", (char *)node3->content);

    // Delete node2 using ft_lstdelone
    ft_lstdelone(node2, del_content);
    
    node1->next = node3;

    // Now, node1->next should be NULL since node2 is deleted
    if (node1->next == NULL)
        printf("\nNode2 has been deleted.\n");
    else
        printf("\nNode2 content after deletion: %s\n",
         (char *)node1->next->content);

    // Clean up the remaining nodes (node1 and node3)
    ft_lstdelone(node1, del_content);
    ft_lstdelone(node3, del_content);

    return 0;
}*/
