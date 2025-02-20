/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:28:42 by sbibers           #+#    #+#             */
/*   Updated: 2024/09/01 09:54:39 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!new)
	{
		return ;
	}
	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		head = *lst;
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = new;
	}
}

// t_list	*ft_lstnew(void *content)
// {
// 	t_list *str;

// 	str = (t_list *) malloc(sizeof(t_list));
// 	str->content = content;
// 	str->next = NULL;
// 	return (str);
// }

// void print_list(t_list *list)
// {
//     while (list)
//     {
//         printf("%s -> ", (char *)list->content);
//         list = list->next;
//     }
//     printf("NULL\n");

// }

// int main()
// {
//     // إنشاء قائمة فارغة
//     t_list *list = NULL;

//     // إنشاء بعض العقد
//     t_list *node1 = ft_lstnew("node1");
//     t_list *node2 = ft_lstnew("node2");
//     t_list *node3 = ft_lstnew("node3");

//     // إضافة العقد إلى نهاية القائمة باستخدام ft_lstadd_back
//     ft_lstadd_back(&list, node1);
//     ft_lstadd_back(&list, node2);
//     ft_lstadd_back(&list, node3);

//     // طباعة القائمة
//     printf("The list after adding nodes to the back:\n");
//     print_list(list);

//     // تحرير الذاكرة
//     free(node1);
//     free(node2);
//     free(node3);

//     return (0);
// }