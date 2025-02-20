/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:40:11 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/17 13:11:42 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*str;

	str = (t_list *)malloc(sizeof(t_list));
	if (!str)
		return (NULL);
	str->content = content;
	str->next = NULL;
	return (str);
}

// void test_ft_lstnew_int()
// {
//     int value = 42;
//     t_list *node = ft_lstnew(&value);

//     if (node != NULL && *(int *)node->content == 42 && node->next == NULL)
//         printf("Test 2 passed.\n");
//     else
//         printf("Test 2 failed.\n");

//     free(node);
// }

// int main()
// {
//     test_ft_lstnew_int();
//     return (0);
// }
