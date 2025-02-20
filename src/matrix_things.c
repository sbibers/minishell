/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:33:31 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:10:12 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_extend_matrix_utils(int *i, char **in, char **out)
{
	out[*i] = ft_strdup(in[*i]);
	if (!out[*i])
	{
		ft_free_matrix(&in);
		ft_free_matrix(&out);
		return (0);
	}
	return (1);
}

static int	ft_extend_matrix_util(int *i, char *new_str)
{
	*i = -1;
	if (!new_str)
		return (0);
	return (1);
}

char	**ft_extend_matrix(char **in, char *new_str)
{
	char	**str;
	int		len;
	int		i;

	str = NULL;
	if (!ft_extend_matrix_util(&i, new_str))
		return (in);
	len = ft_matrixlen(in);
	str = malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	str[len + 1] = NULL;
	while (++i < len)
	{
		if (!ft_extend_matrix_utils(&i, in, str))
			return (NULL);
	}
	str[i] = ft_strdup(new_str);
	if (!str[i])
	{
		ft_free_matrix(&in);
		return (NULL);
	}
	ft_free_matrix(&in);
	return (str);
}
