/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:00 by mabuyahy          #+#    #+#             */
/*   Updated: 2025/02/19 20:00:58 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countchar(char *str, char c)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

// take one string with char.
int	ft_strchr_index(const char *str, int c)
{
	unsigned char	cha;
	int				i;

	i = 0;
	if (!str)
		return (-1);
	cha = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == cha)
			return (i);
		i++;
	}
	if (cha == '\0')
		return (i);
	return (-1);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_space(char *read)
{
	int	i;

	i = 0;
	while (read[i] && read[i] == ' ')
		i++;
	if (read[i] != '\0')
		return (1);
	return (0);
}

void	*handle_exit_null(void)
{
	printf("exit\n");
	return (NULL);
}
