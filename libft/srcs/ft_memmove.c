/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:06:57 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/28 16:50:26 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	if (n == 0)
		return (dest);
	if (src == 0 && dest == 0)
		return (NULL);
	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	if (csrc < cdest && cdest < csrc + n)
	{
		cdest += n;
		csrc += n;
		while (n--)
			*(--cdest) = *(--csrc);
	}
	else
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	return (dest);
}

/*
int	main(void)
{
	char	buffer[20];
	char	source[];
    char dest[20];

    buffer[20] = "Hello, World!";
    
    ft_memmove(buffer + 7, buffer, 1);
    printf("%s\n", buffer); // Should print "Hello, Hello, World!"
    // Example where src and dest do not overlap
    source[] = "123456789";
    ft_memmove(dest, source, 9);
    dest[9] = '\0'; // Null-terminate the destination
    printf("%s\n", dest); // Should print "123456789"
    return (0);
}
*/
