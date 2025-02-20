/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:50:42 by sbibers           #+#    #+#             */
/*   Updated: 2024/11/29 22:25:37 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_prt_unsigned(unsigned int n)
{
	if (n < 10)
	{
		ft_prt_c(n + 48);
	}
	else
	{
		ft_prt_unsigned(n / 10);
		ft_prt_unsigned(n % 10);
	}
}

int	ft_unsigned(unsigned int n)
{
	ft_prt_unsigned(n);
	return (ft_dec_len(n));
}
