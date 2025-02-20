/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:56:47 by sbibers           #+#    #+#             */
/*   Updated: 2024/09/01 09:39:33 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*srcs;
	unsigned char		*dests;
	size_t				i;

	if (n == 0)
	{
		return (dest);
	}
	if (dest == 0 && src == 0)
	{
		return (NULL);
	}
	srcs = (const unsigned char *)src;
	dests = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		dests[i] = srcs[i];
		i++;
	}
	return (dest);
}
