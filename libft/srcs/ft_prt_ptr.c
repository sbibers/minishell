/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:50:19 by sbibers           #+#    #+#             */
/*   Updated: 2024/11/29 22:22:00 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(char *str)
{
	int	i;
	int	byte;

	byte = 0;
	while (str[byte] != '\0')
	{
		byte++;
	}
	i = byte - 1;
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
	return (byte);
}

char	ft_decimal_to_hex(char digit, char t)
{
	int	c;

	c = 0;
	if (t == 'X')
		c = 32;
	if (digit > 9)
	{
		if (digit == 10)
			return ('a' - c);
		if (digit == 11)
			return ('b' - c);
		if (digit == 12)
			return ('c' - c);
		if (digit == 13)
			return ('d' - c);
		if (digit == 14)
			return ('e' - c);
		if (digit == 15)
			return ('f' - c);
	}
	else
		return (digit + 48);
	return (0);
}

int	ft_hex_len(unsigned long add)
{
	int	len;

	len = 0;
	while (add > 0)
	{
		add /= 16;
		len++;
	}
	return (len);
}

int	ft_prt_ptr(unsigned long add)
{
	char	*ptr;
	int		byte;
	int		count;

	count = 0;
	if (!add)
		return (write(1, "(nil)", 5));
	byte = write(1, "0x", 2);
	ptr = (char *)malloc((ft_hex_len(add) + 1));
	while (add)
	{
		ptr[count] = ft_decimal_to_hex(add % 16, 'x');
		add /= 16;
		count++;
	}
	ptr[count] = '\0';
	byte = byte + ft_print_hex(ptr);
	free(ptr);
	ptr = NULL;
	return (byte);
}
