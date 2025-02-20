/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:44:57 by sbibers           #+#    #+#             */
/*   Updated: 2024/09/01 09:44:42 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!del || !lst)
        return ;
        del(lst->content);
    free(lst);
}
void	delet(void *content)
{
    free(content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*str;

	if (lst)
	{
		while (*lst)
		{
			str = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = str;
		}
	}
}
