/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:30 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/27 20:27:05 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*string;

	string = (const unsigned char *)s;
	while (n--)
	{
		if (*string == (unsigned char)c)
			return ((void *)string);
		string++;
	}
	return (NULL);
}
