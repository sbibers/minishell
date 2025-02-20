/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:08:29 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/31 17:13:34 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// t_list  *ft_lstnew(void *content)
// {
//     t_list *node = malloc(sizeof(t_list));
//     if (node)
//     {
//         node->content = content;
//         node->next = NULL;
//     }
//     return (node);
// }

// void    print_list(t_list *list)
// {
//     while (list) {
//         printf("%s -> ", (char *)list->content);
//         list = list->next;
//     }
//     printf("NULL\n");
// }

// int main() {
//     t_list *list = 0;

//     t_list *node1 = ft_lstnew("node1");
//     t_list *node2 = ft_lstnew("node2");
//     t_list *node3 = ft_lstnew("node3");
//     ft_lstadd_front(&list, node1);
//     ft_lstadd_front(&list, node2);
//     ft_lstadd_front(&list, node3);
//     printf("The list after adding nodes at the front:\n");
//     print_list(list);
//     return (0);
// }
