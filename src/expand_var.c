/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:51:42 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 17:57:23 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static void	expand_variable_util(t_expand_read_2 *var,
									char *line,
									int prefix_len)
{
	ft_strncpy(var->expanded, line, prefix_len);
	var->expanded[prefix_len] = '\0';
	ft_strcat(var->expanded, var->env_value);
	free(var->env_value);
	ft_strcat(var->expanded, var->key_eend);
	free(line);
}

static char	*expand_variable(char *line, char *key_start, t_prompt *prom)
{
	t_expand_read_2	var;

	var.key_eend = key_start;
	while (*var.key_eend && (ft_isalnum(*var.key_eend) || *var.key_eend == '?'
			|| *var.key_eend == '_'))
		var.key_eend++;
	var.len = var.key_eend - key_start;
	var.key = ft_strndup(key_start, var.len);
	if (!var.key)
		return (line);
	var.env_value = get_env_var(var.key, prom->envp, -1, prom);
	free(var.key);
	if (!var.env_value)
		var.env_value = ft_strdup("");
	var.new_len = ft_strlen(line) - var.len + ft_strlen(var.env_value);
	var.expanded = ft_calloc(var.new_len + 1, 1);
	if (!var.expanded)
	{
		free(var.env_value);
		return (line);
	}
	var.prefix_len = key_start - line - 1;
	expand_variable_util(&var, line, var.prefix_len);
	return (var.expanded);
}

static void	init_expand_read(t_expand_read *var, char *line)
{
	var->in_double_quote = 0;
	var->in_single = 0;
	var->ptr = NULL;
	var->offset = 0;
	var->new_line = NULL;
	var->ptr = line;
}

// remove $
char	*expand_variables(t_prompt *prom, char *line)
{
	t_expand_read	var;

	if (!line)
		return (NULL);
	init_expand_read(&var, line);
	while (*var.ptr)
	{
		if (*var.ptr == '\'' && !var.in_double_quote)
			var.in_single = !var.in_single;
		else if (*var.ptr == '"' && !var.in_single)
			var.in_double_quote = !var.in_double_quote;
		else if (*var.ptr == '$' && !var.in_single && *(var.ptr + 1) != '~')
		{
			var.offset = var.ptr - line;
			var.new_line = expand_variable(line, var.ptr + 1, prom);
			if (!var.new_line)
				return (line);
			var.ptr = var.new_line + var.offset;
			line = var.new_line;
		}
		var.ptr++;
	}
	return (line);
}
