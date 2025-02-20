/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:17:25 by mabuyahy          #+#    #+#             */
/*   Updated: 2025/02/20 20:06:11 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*str;

	str = dest;
	while (*str)
		str++;
	while (*src)
	{
		*str = *src;
		str++;
		src++;
	}
	*str = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	char	*str;

	str = dest;
	while (n > 0 && *src)
	{
		*str = *src;
		str++;
		src++;
		n--;
	}
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
	return (dest);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	char	*d;
	int		len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	d = dup;
	while (len > 0)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
	*d = '\0';
	return (dup);
}

int	if_split_separator_util(char *str,
char *sep, int i[3], int quotes[2])
{
	if (str[i[0]] && (!ft_strchr(sep, str[i[0]]) || quotes[0] || quotes[1]))
		return (1);
	return (0);
}

void	stop_check_cmd(char *path, t_list *cmd, char ***s, t_prompt *prom)
{
	if (path)
		free(path);
	if (s)
		ft_free_matrix(s);
	stop_make_node(cmd, NULL, prom->envp);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}
