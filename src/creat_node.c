/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:09:14 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fail_make_node(char ***temp, char **command, t_prompt *prom,
		t_list **cmds)
{
	ft_free_matrix(temp);
	stop_make_node(cmds[0], prom->envp, command);
	stop_make_node(cmds[1], NULL, NULL);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}

static int	creat_node(char **command, int *i, t_list **cmds)
{
	t_node_content	*mini;
	t_list			*lst;

	if (command[*i][0] == '|' && (*i != 0))
		(*i)++;
	mini = init_node_content();
	if (!mini)
		return (0);
	lst = ft_lstnew(mini);
	if (!lst)
		return (0);
	ft_lstadd_back(&cmds[0], lst);
	cmds[1] = ft_lstlast(cmds[0]);
	return (1);
}

// temp[1] = all commands without single and double quotes.
// temp[0] = all commands with single and double quotes.
// cmd[0] = pointer to the first | cmd[1] = pointer to the last.
// fill node, put the command inside the content of the node.
// every command have the input and output and the path of the command.
t_list	*make_node(char **command, t_prompt *prom)
{
	t_list		*cmds[2];
	t_fill_node	fill;

	prom->count_make_node = -1;
	init_make_node(cmds, &fill, command, prom);
	while (command[++prom->count_make_node])
	{
		make_node_util(cmds, &fill, &prom->count_make_node);
		if (prom->count_make_node == 0
			|| (command[prom->count_make_node][0] == '|'
			&& command[prom->count_make_node + 1]
			&& command[prom->count_make_node + 1][0]))
			if (!creat_node(command, &prom->count_make_node, cmds))
				hanlde_make_node(cmds, command, prom, fill.temp);
		make_node_util_2(command, &fill, cmds, prom);
		if (!cmds[1]->content)
			fail_make_node(fill.temp, command, prom, cmds);
		if (prom->count_make_node < 0)
			return (stop_make_node(cmds[0], command, fill.temp[1]));
		if (!command[prom->count_make_node])
			break ;
	}
	stop_make_node(NULL, fill.temp[1], command);
	return (cmds[0]);
}
