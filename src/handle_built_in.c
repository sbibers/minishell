/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:50:57 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 19:46:31 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_e_status;

static void	to_executer(t_prompt *prom, t_list *cmd, char **args)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	execute_command(prom, cmd, args);
}

static void	count_and_check(char **str, int *size)
{
	if (str)
		*size = ft_strlen(*str);
}

// execute command, and check if the command built in.
int	handle_built_in(t_prompt *prom, t_list *cmd, int *exit_num, char **command)
{
	char	**str;
	int		size;

	while (cmd)
	{
		str = ((t_node_content *)cmd->content)->full_cmd;
		size = 0;
		count_and_check(str, &size);
		if (str && !ft_strncmp(*str, "exit", size) && size == 4)
			prom->exit_status = handle_exit(cmd, exit_num, prom);
		else if (!cmd->next && prom->size == 1 && str
			&& !ft_strncmp(*str, "cd", size) && size == 2)
			prom->exit_status = handle_cd(prom, cmd, command);
		else if (!cmd->next && str && prom->size == 1
			&& !ft_strncmp(*str, "export", size)
			&& size == 6 && ft_matrixlen(str) > 1)
			prom->exit_status = handle_export(prom, cmd, command);
		else if (!cmd->next && prom->size == 1 && str
			&& !ft_strncmp(*str, "unset", size) && size == 5)
			prom->exit_status = handle_unset(prom, cmd, command);
		else
			to_executer(prom, cmd, command);
		cmd = cmd->next;
	}
	return (prom->exit_status);
}

static int	check_back_slash(t_node_content *node)
{
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/'))
		|| (node->full_path && ft_strchr(node->full_path, '/')))
	{
		return (0);
	}
	return (1);
}

int	check_if_built_in(t_node_content *node)
// check if the command built in or not.
{
	int	size;

	if (!node->full_cmd)
		return (0);
	if (!check_back_slash(node))
		return (0);
	size = ft_strlen(*node->full_cmd);
	if (ft_strncmp(*node->full_cmd, "exit", size) == 0 && size == 4)
		return (1);
	if (ft_strncmp(*node->full_cmd, "cd", size) == 0 && size == 2)
		return (1);
	if (ft_strncmp(*node->full_cmd, "pwd", size) == 0 && size == 3)
		return (1);
	if (ft_strncmp(*node->full_cmd, "export", size) == 0 && size == 6)
		return (1);
	if (ft_strncmp(*node->full_cmd, "env", size) == 0 && size == 3)
		return (1);
	if (ft_strncmp(*node->full_cmd, "unset", size) == 0 && size == 5)
		return (1);
	if (ft_strncmp(*node->full_cmd, "echo", size) == 0 && size == 4)
		return (1);
	return (0);
}
