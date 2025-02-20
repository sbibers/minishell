/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:49:53 by sbibers           #+#    #+#             */
/*   Updated: 2024/11/29 22:20:08 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(va_list arg, char c)
{
	int	byte;

	byte = 0;
	if (c == '%')
	{
		write(1, "%", 1);
		byte++;
	}
	if (c == 'c')
		byte = byte + ft_prt_c(va_arg(arg, int));
	if (c == 's')
		byte = byte + ft_prt_s(va_arg(arg, char *));
	if (c == 'd' || c == 'i')
		byte = byte + ft_prt_id(va_arg(arg, int));
	if (c == 'u')
		byte = byte + ft_unsigned(va_arg(arg, int));
	if (c == 'p')
		byte = byte + ft_prt_ptr(va_arg(arg, unsigned long));
	if (c == 'x' || c == 'X')
		byte = byte + ft_prt_x(va_arg(arg, unsigned int), c);
	return (byte);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		count;
	int		byte;
	char	ch;

	count = 0;
	byte = 0;
	va_start(arg, str);
	while (str[count] != '\0')
	{
		if (str[count] == '%')
		{
			ch = str[count + 1];
			byte = byte + ft_check(arg, ch);
			count++;
		}
		else
			byte = byte + write(1, &str[count], 1);
		count++;
	}
	va_end(arg);
	return (byte);
}
