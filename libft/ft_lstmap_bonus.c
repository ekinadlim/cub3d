/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:53 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/20 19:34:50 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_create_node(t_list *temp, t_list *new_head,
				void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	void	*new_content;

	new_content = f(temp->content);
	if (new_content == 0)
	{
		ft_lstclear(&new_head, del);
		return (0);
	}
	new_node = ft_lstnew(new_content);
	if (new_node == 0)
	{
		del(new_content);
		ft_lstclear(&new_head, del);
		return (0);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new_node;
	t_list	*new_head;
	t_list	*last_node;

	if (lst == 0 || f == 0)
		return (0);
	temp = lst;
	new_head = 0;
	last_node = 0;
	while (temp)
	{
		new_node = ft_create_node(temp, new_head, f, del);
		if (new_node == 0)
			return (0);
		if (new_head == 0)
			new_head = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		temp = temp->next;
	}
	return (new_head);
}

/*void *my_function(void *content) {
    return strdup((char *)content); // Duplicate the string
}
void my_del(void *content) {
    free(content);
}

int main() {
    // Create original list
    t_list *original = ft_lstnew(ft_strdup("hello!"));
    original->next = ft_lstnew(ft_strdup("world"));
    
    // Print original list
    printf("Original list:\n");
    for (t_list *temp = original; temp != NULL; temp = temp->next) {
        printf("%s\n", (char *)temp->content);
    }

    // Create new list using ft_lstmap
    t_list *new_list = ft_lstmap(original, my_function, my_del);

    // Print new list
    printf("\nNew list:\n");
    for (t_list *temp = new_list; temp != NULL; temp = temp->next) {
        printf("%s\n", (char *)temp->content); // Print the length of each string
    }
    
    printf("\nOriginal list:\n");
    for (t_list *temp = original; temp != NULL; temp = temp->next) {
        printf("%s\n", (char *)temp->content);
    }

    // Free the original list
    ft_lstclear(&original, free);
    // Free the new list
    ft_lstclear(&new_list, free);

    return 0;
}*/
