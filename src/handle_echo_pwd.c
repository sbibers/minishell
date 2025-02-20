/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:15:34 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 17:58:30 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static int	should_skip_newline(char *arg)
{
	if (!ft_strncmp(arg, "-n", 2))
	{
		if (ft_countchar(arg, 'n') == (int)(ft_strlen(arg) - 1))
			return (1);
	}
	return (0);
}

static void	print_echo(char **command, int start)
{
	int	i;

	i = start;
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	handle_echo(t_list *cmd)
// handle echooooooo
{
	int				flag_line;
	int				i;
	char			**command;
	t_node_content	*node;

	flag_line = 1;
	node = cmd->content;
	command = node->full_cmd;
	i = 1;
	while (command && command[i] && should_skip_newline(command[i]))
	{
		flag_line = 0;
		i++;
	}
	print_echo(command, i);
	if (flag_line)
		write(1, "\n", 1);
	else
		return (0);
	return (1);
}

int	handle_pwd(void)
// handle pwd.
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
