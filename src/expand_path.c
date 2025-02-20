/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:57:08 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 17:57:16 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static void	update_quotes(char c, int quotes[2])
{
	if (c == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
	else if (c == '"' && !quotes[0])
		quotes[1] = !quotes[1];
}

static char	*handle_fail_expand_path(char *temp, char *path, char *var)
{
	if (path)
		free(path);
	if (temp)
		free(temp);
	if (var)
		free(var);
	return (NULL);
}

char	*replace_tilde(char *str, int *i, char *var)
{
	char	*temp;
	char	*path;
	char	*new_str;

	temp = ft_substr(str, 0, *i);
	if (!temp)
		return (handle_fail_expand_path(NULL, str, var));
	path = ft_strjoin(temp, var);
	free(temp);
	if (!path)
		return (handle_fail_expand_path(temp, NULL, var));
	new_str = ft_strjoin(path, str + *i + 1);
	free(path);
	if (!new_str)
		return (handle_fail_expand_path(NULL, NULL, var));
	free(str);
	*i = *i + ft_strlen(var) - 1;
	return (new_str);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		update_quotes(str[i], quotes);
		if (!quotes[0] && !quotes[1] && str[i] == '~'
			&& (i == 0 || str[i - 1] != '$'))
			str = replace_tilde(str, &i, var);
		if (!str)
			return (NULL);
	}
	free(var);
	return (str);
}
