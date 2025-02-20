/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:10:07 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/29 16:42:40 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
int	main(void)
{
	int		fd;
	char	x;

    fd = open("ron.txt", O_CREAT | O_WRONLY);
    if (fd == -1)
    {
        printf("%s", "error");
    }
    x = 'c';
    ft_putchar_fd(x, fd);
    close (fd);
}
*/