/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:21:27 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:00:29 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*stop_make_node(t_list *cmds, char **str_1, char **str_2)
{
	if (cmds)
		ft_lstclear(&cmds, free_content);
	if (str_2 && str_2[0])
		ft_free_matrix(&str_2);
	if (str_1 && str_1[0])
		ft_free_matrix(&str_1);
	return (NULL);
}

int	ft_matrixlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_free_matrix(char ***str)
{
	int	i;

	i = 0;
	while (str && str[0] && str[0][i])
	{
		free(str[0][i]);
		i++;
	}
	if (str)
	{
		free(str[0]);
		*str = NULL;
	}
}

char	**ft_dup_matrix(char **m)
{
	char	**str;
	int		n;
	int		i;

	i = 0;
	n = ft_matrixlen(m);
	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	while (m[i])
	{
		str[i] = ft_strdup(m[i]);
		if (!str[i])
		{
			ft_free_matrix(&str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	ft_putmatrix_fd(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (nl)
			count += ft_putendl_fd(m[i], fd);
		else
			count += ft_putstr_fd(m[i], fd);
		i++;
	}
	return (count);
}
