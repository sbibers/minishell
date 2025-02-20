/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuyahy <mabuyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:43:44 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/10 18:21:01 by mabuyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return (ft_strlen(s) + 1);
	}
	return (0);
}

// int main()
// {
//     char *file_name = "salam.txt";

//     int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         printf("%s", "error");
//     }
//     ft_putendl_fd("ronaldo", fd);
//     close (fd);
//     return (0);
// }