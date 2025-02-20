/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:50:35 by sbibers           #+#    #+#             */
/*   Updated: 2024/11/29 22:24:47 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_prt_x(unsigned int n, char c)
{
	char	*ptr;
	int		byte;
	int		count;

	count = 0;
	if (!n)
		return (write(1, "0", 1));
	ptr = (char *)malloc(ft_hex_len(n) + 1);
	while (n)
	{
		ptr[count] = ft_decimal_to_hex(n % 16, c);
		n /= 16;
		count++;
	}
	ptr[count] = '\0';
	byte = ft_print_hex(ptr);
	free(ptr);
	return (byte);
}
