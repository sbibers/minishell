/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:34:17 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:13:16 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quotes_count(char *str, int *quotes, int *j)
{
	if (str[*j] == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
	if (str[*j] == '\"' && !quotes[0])
		quotes[1] = !quotes[1];
}

static int	count_words(char *str, char *set, int count, int *j)
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[*j] != '\0')
	{
		count++;
		if (!ft_strchr(set, str[*j]))
		{
			while ((!ft_strchr(set, str[*j]) || quotes[0]
					|| quotes[1]) && str[*j] != '\0')
			{
				update_quotes_count(str, quotes, j);
				(*j)++;
			}
			if (quotes[0] || quotes[1])
				return (-1);
		}
		else
			(*j)++;
	}
	return (count);
}

static void	update_quotes_fill(char *str, int *i, int *quotes)
{
	if (str[i[0]] == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
	if (str[i[0]] == '\"' && !quotes[0])
		quotes[1] = !quotes[1];
}

static char	**split_separator_util(char **args, char *str, char *sep, int i[3])
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(sep, str[i[0]]))
		{
			while (if_split_separator_util(str, sep, i, quotes))
			{
				update_quotes_fill(str, i, quotes);
				i[0]++;
			}
		}
		else
			i[0]++;
		args[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
		if (!args[i[2] - 1])
		{
			ft_free_matrix(&args);
			return (NULL);
		}
	}
	return (args);
}

char	**split_separator(char const *s, char *sep)
// split string by |, <, >
{
	char	**words;
	int		count_word;
	int		i[3];
	int		j;

	j = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	count_word = count_words((char *)s, sep, 0, &j);
	if (count_word == -1)
		return (NULL);
	words = malloc((count_word + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	words = split_separator_util(words, (char *)s, sep, i);
	words[count_word] = NULL;
	return (words);
}
