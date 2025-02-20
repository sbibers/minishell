/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:31:29 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
// check if the argument exist in env variable.
int	found_var(char *argv, char **envp, int *i)
{
	int	pos;

	*i = 0;
	pos = ft_strchr_index(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[*i])
	{
		if (!ft_strncmp(envp[*i], argv, pos + 1))
			return (1);
		(*i)++;
	}
	return (0);
}

static void	edit_env(t_prompt *prom, t_list *cmd, char **command, char *arg)
{
	int	i;
	int	index;

	index = found_var(arg, prom->envp, &i);
	if (index == 1)
	{
		free(prom->envp[i]);
		prom->envp[i] = ft_strdup(arg);
		if (!prom->envp[i])
		{
			stop_make_node(cmd, command, prom->envp);
			print_error(ALLOC, NULL, 1, prom);
			exit(1);
		}
	}
	else if (!index)
	{
		prom->envp = ft_extend_matrix(prom->envp, arg);
		if (!prom->envp)
		{
			stop_make_node(cmd, command, NULL);
			print_error(ALLOC, NULL, 1, prom);
			exit(1);
		}
	}
}

int	handle_export(t_prompt *prom, t_list *cmd, char **command)
{
	char	**str;
	int		i;

	str = ((t_node_content *)prom->cmds->content)->full_cmd;
	i = 1;
	while (str[i])
	{
		edit_env(prom, cmd, command, str[i]);
		i++;
	}
	return (0);
}
