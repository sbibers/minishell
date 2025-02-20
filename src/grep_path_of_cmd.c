/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep_path_of_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find the file of the command in a PATH.
static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

void	check_command_path(t_list *cmd, char ***s, char *path, t_prompt *prom)
{
	t_node_content	*n;
	DIR				*dir;

	n = cmd->content;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (!check_if_built_in(n) && n && n->full_cmd && !dir)
	{
		path = get_env_var("PATH", prom->envp, 4, prom);
		if (path)
		{
			*s = ft_split(path, ':');
			if (!*s)
				stop_check_cmd(path, cmd, s, prom);
		}
		free(path);
		n->full_path = find_command(*s, *n->full_cmd, n->full_path);
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			print_error(NOT_CMD, *n->full_cmd, 127, prom);
	}
	if (dir)
		closedir(dir);
}

DIR	*check_directory(t_list *cmd, char ***s, char *path, t_prompt *prom)
{
	t_node_content	*n;
	DIR				*dir;

	dir = NULL;
	n = cmd->content;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
	{
		*s = ft_split(*n->full_cmd, '/');
		if (!*s)
			stop_check_cmd(path, cmd, s, prom);
		n->full_path = ft_strdup(*n->full_cmd);
		if (!n->full_path)
			stop_check_cmd(path, cmd, s, prom);
		free(n->full_cmd[0]);
		n->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
		if (!n->full_cmd[0])
			stop_check_cmd(path, cmd, s, prom);
	}
	else
		check_command_path(cmd, s, path, prom);
	return (dir);
}

static void	grep_path_of_cmd(t_prompt *prom, t_list *cmd, char **str,
		char *path)
{
	t_node_content	*node;
	DIR				*dir;

	node = cmd->content;
	dir = check_directory(cmd, &str, path, prom);
	if (!check_if_built_in(node) && node && node->full_cmd && dir)
		print_error(IS_DIR, *node->full_cmd, 126, prom);
	else if (!check_if_built_in(node) && node && node->full_path
		&& access(node->full_path, F_OK) == -1)
		print_error(ERR_NODIR, node->full_path, 127, prom);
	else if (!check_if_built_in(node) && node && node->full_path
		&& access(node->full_path, X_OK) == -1)
		print_error(NO_PERM, node->full_path, 126, prom);
	if (dir)
		closedir(dir);
	ft_free_matrix(&str);
}

// execute the command, if the command does not built in.
void	execute_command(t_prompt *prom, t_list *cmd, char **command)
{
	int	pipes[2];

	grep_path_of_cmd(prom, cmd, NULL, NULL);
	if (pipe(pipes) == -1)
	{
		print_error(PIPE_ERR, NULL, 1, prom);
		return ;
	}
	if (!check_to_execute(prom, cmd, pipes, command))
		return ;
	close(pipes[1]);
	if (cmd->next && !((t_node_content *)cmd->next->content)->in)
		((t_node_content *)cmd->next->content)->in = pipes[0];
	else
		close(pipes[0]);
	if (((t_node_content *)cmd->content)->in > 1)
		close(((t_node_content *)cmd->content)->in);
	if (((t_node_content *)cmd->content)->out > 1)
		close(((t_node_content *)cmd->content)->out);
}
