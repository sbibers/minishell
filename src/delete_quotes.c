/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:56:33 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:28:16 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quotes_malloc(const char *str, int *double_q, int *single_q,
		int *i)
{
	if (!*double_q && str[*i] == '\'')
		*single_q = !*single_q;
	if (!*single_q && str[*i] == '\"')
		*double_q = !*double_q;
}

static int	malloc_len(char const *str)
{
	int	count;
	int	i;
	int	dpuble_q;
	int	single_q;

	i = 0;
	count = 0;
	dpuble_q = 0;
	single_q = 0;
	while (str && str[i])
	{
		update_quotes_malloc(str, &dpuble_q, &single_q, &i);
		if ((str[i] == '\"' && !single_q) || (str[i] == '\'' && !dpuble_q))
			count++;
		i++;
	}
	if (single_q || dpuble_q)
		return (-1);
	return (count);
}

static void	update_quotes_trim(const char *str, int *double_q, int *single_q,
		int *i)
{
	if (!*double_q && str[i[0]] == '\'')
		*single_q = !*single_q;
	if (!*single_q && str[i[0]] == '\"')
		*double_q = !*double_q;
}

char	*delete_qoutes(char const *str, int single_q, int double_q)
// return the string without ' and ".
{
	int		count;
	int		i[2];
	char	*temp;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(str);
	if (!str || count == -1)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!temp)
		return (NULL);
	while (str[i[0]])
	{
		update_quotes_trim(str, &double_q, &single_q, i);
		if ((str[i[0]] != '\"' || single_q) && (str[i[0]] != '\'' || double_q)
			&& ++i[1] >= 0)
			temp[i[1]] = str[i[0]];
		i[0]++;
	}
	temp[++i[1]] = '\0';
	return (temp);
}
