/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:24:02 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/27 20:26:45 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	char	value;
	size_t	i;

	i = 0;
	ptr = s;
	value = (char)c;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (s);
}
