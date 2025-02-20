/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:28:47 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

// if (flags[0] && flags[1]) // >>
// else if (flags[0] && !flags[1]) // >
// flags[0] = 1 write, 0 read.
// flags[1] = 1 append, 0 trunc.
static int	get_fd(int prev_file, char *file_path, int flags[2], t_prompt *prom)
{
	int	fd;

	if (prev_file > 2)
		close(prev_file);
	if (!file_path)
		return (-1);
	if (access(file_path, F_OK) == -1 && !flags[0])
		print_error(ERR_NODIR, file_path, 127, prom);
	else if (!flags[0] && access(file_path, R_OK) == -1)
		print_error(NO_PERM, file_path, 126, prom);
	else if (flags[0] && access(file_path, W_OK) == -1
		&& access(file_path, F_OK) == 0)
		print_error(NO_PERM, file_path, 126, prom);
	if (flags[0] && flags[1])
		fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && prev_file != -1)
		fd = open(file_path, O_RDONLY);
	else
		fd = prev_file;
	return (fd);
}

// >
t_node_content	*out_redirction_single(t_node_content *node, char **command,
int *i, t_prompt *prom)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (command[*i])
		node->out = get_fd(node->out, command[*i], flags, prom);
	if (!command[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out == -1)
			prom->exit_status = 1;
		else
		{
			ft_putstr_fd("minishell: syntax error", 2);
			ft_putendl_fd(" near unexpected token `newline'", 2);
			prom->exit_status = 2;
		}
	}
	return (node);
}

// args  with expanding.
// node = content.
// >>
// flags[0] = 1 write, 0 read.
// flags[1] = 1 append, 0 trunc.
t_node_content	*out_redirction_double(t_node_content *node, char **command,
int *i, t_prompt *prom)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	*i += 2;
	if (command[*i])
		node->out = get_fd(node->out, command[*i], flags, prom);
	if (!command[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out == -1)
			prom->exit_status = 1;
		else
		{
			ft_putstr_fd("minishell: syntax error", 2);
			ft_putendl_fd(" near unexpected token `newline'", 2);
			prom->exit_status = 2;
		}
	}
	return (node);
}

// for infile.
t_node_content	*in_redirection(t_node_content *node,
char **command, int *i, t_prompt *promt)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (command[*i])
		node->in = get_fd(node->in, command[*i], flags, promt);
	if (!command[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in == -1)
			promt->exit_status = 1;
		else
		{
			ft_putstr_fd("minishell: syntax error", 2);
			ft_putendl_fd(" near unexpected token `newline'", 2);
			promt->exit_status = 2;
		}
	}
	return (node);
}

// for heardoc.
t_node_content	*herdoc(t_node_content *node,
char **command, int *i, t_prompt *prom)
{
	char	*temp[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	temp[0] = NULL;
	temp[1] = "minishell: warning: here-document delimited by end-of-file";
	*i += 2;
	if (command[*i])
	{
		temp[0] = command[*i];
		node->in = handle_herdoc(str, temp, prom);
	}
	if (!command[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in != -1)
		{
			ft_putstr_fd("minishell: syntax error", 2);
			ft_putendl_fd(" near unexpected token `newline'", 2);
			prom->exit_status = 2;
		}
	}
	return (node);
}
