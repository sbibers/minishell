/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:48 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:28:23 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_export(char **str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		ft_putstr_fd("export : ", fd);
		ft_putstr_fd(str[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

static void	child_check_built_in(t_node_content *n, size_t *size,
		t_prompt *prompt, t_list *cmd)
{
	if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", *size) && *size == 3)
	{
		prompt->exit_status = handle_pwd();
		ft_free_matrix(&prompt->envp);
	}
	else if (check_if_built_in(n) && n->full_cmd && !ft_strncmp(*n->full_cmd,
			"echo", *size) && *size == 4)
	{
		prompt->exit_status = handle_echo(cmd);
		ft_free_matrix(&prompt->envp);
	}
	else if (check_if_built_in(n) && n->full_cmd && !ft_strncmp(*n->full_cmd,
			"env", *size) && *size == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		ft_free_matrix(&prompt->envp);
		prompt->exit_status = 0;
	}
}

// execute the command and check the command.
void	execve_the_command(t_prompt *prompt, t_node_content *node, t_list *cmd,
		char **command)
{
	size_t	size;

	if (prompt->flag == 1)
		return (ft_free_matrix(&prompt->envp));
	if (node->full_cmd)
		size = ft_strlen(*node->full_cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!check_if_built_in(node) && node->full_cmd)
		execve(node->full_path, node->full_cmd, prompt->envp);
	else if (check_if_built_in(node) && node->full_cmd
		&& !ft_strncmp(*node->full_cmd, "cd", size) && size == 2)
	{
		prompt->exit_status = handle_cd(prompt, cmd, command);
		ft_free_matrix(&prompt->envp);
	}
	else if (check_if_built_in(node) && node->full_cmd
		&& !ft_strncmp(*node->full_cmd, "export", size) && size == 6)
	{
		put_export(prompt->envp, 1);
		ft_free_matrix(&prompt->envp);
	}
	else
		child_check_built_in(node, &size, prompt, cmd);
}
