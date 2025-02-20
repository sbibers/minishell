/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:50:12 by sbibers           #+#    #+#             */
/*   Updated: 2024/11/29 22:21:22 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_prt_c('-');
		ft_prt_c('2');
		ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		ft_prt_c('-');
		n = -n;
		ft_putnbr(n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_prt_c(n + '0');
	}
}

int	ft_prt_id(int n)
{
	ft_putnbr(n);
	return (ft_dec_len(n));
}
