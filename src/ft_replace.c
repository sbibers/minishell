/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:09:52 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:28:38 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_copy_big_row(char **temp, char **big, int *i, int n)
{
	if (i[0] != n)
	{
		temp[++i[2]] = ft_strdup(big[i[0]]);
		if (!temp[i[2]])
		{
			ft_free_matrix(&temp);
			return (NULL);
		}
	}
	return (temp);
}

static char	**ft_insert_small_rows(char **temp, char **small, int *i)
{
	while (small && small[++i[1]])
	{
		temp[++i[2]] = ft_strdup(small[i[1]]);
		if (!temp[i[2]])
		{
			ft_free_matrix(&temp);
			return (NULL);
		}
	}
	return (temp);
}

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**temp;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	temp = ft_calloc(ft_matrixlen(*big) + ft_matrixlen(small), sizeof(char *));
	if (!temp)
		return (NULL);
	while (temp && (*big)[++i[0]])
	{
		if (i[0] != n)
			temp = ft_copy_big_row(temp, *big, i, n);
		else
			temp = ft_insert_small_rows(temp, small, i);
		if (!temp)
			return (NULL);
	}
	ft_free_matrix(big);
	*big = temp;
	return (*big);
}
