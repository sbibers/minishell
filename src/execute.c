/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:17:22 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static void	*dup_in_out(t_list *cmd, int fd[2], t_prompt *prom)
// redirection the command to input and output file or pipe.
{
	t_node_content	*node;

	node = cmd->content;
	if (node->in != 0)
	{
		if (dup2(node->in, 0) == -1)
			return (print_error(DUP_ERR, NULL, 1, prom));
		close(node->in);
	}
	if (node->out != 1)
	{
		if (dup2(node->out, 1) == -1)
			return (print_error(DUP_ERR, NULL, 1, prom));
		close(node->out);
	}
	else if (cmd->next && dup2(fd[1], 1) == -1)
		return (print_error(DUP_ERR, NULL, 1, prom));
	close(fd[1]);
	return ("");
}

static void	*executer_2(t_prompt *prompt, t_list *cmd, int fd[2],
		char **command)
// after make fork this is chiled process.
{
	t_node_content	*node;

	node = cmd->content;
	dup_in_out(cmd, fd, prompt);
	close(fd[0]);
	execve_the_command(prompt, node, cmd, command);
	ft_lstclear(&prompt->cmds, free_content);
	exit(prompt->exit_status);
}

static void	executer(t_prompt *prompt, t_list *cmd, int pipes[2], char **args)
// make chiled process.
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_error(FORK_ERR, NULL, 1, prompt);
		close(pipes[1]);
		close(pipes[0]);
	}
	else if (pid == 0)
		executer_2(prompt, cmd, pipes, args);
}

int	check_to_execute(t_prompt *prom, t_list *cmd, int pipes[2], char **command)
// check the command before make chiled process.
{
	t_node_content	*node;
	DIR				*directory;

	node = cmd->content;
	directory = NULL;
	if (node->full_cmd)
		directory = opendir(*node->full_cmd);
	if (node->in == -1 || node->out == -1)
		return (0);
	if ((node->full_path && node->full_cmd[0][0] != '\0'
		&& access(node->full_path, X_OK) == 0)
		|| check_if_built_in(node))
	{
		executer(prom, cmd, pipes, command);
		if (prom->exit_status != 0 && prom->flag == 0)
			prom->exit_status = 0;
	}
	if (directory)
		closedir(directory);
	return (1);
}
