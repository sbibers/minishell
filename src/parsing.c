/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:59:46 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static void	handle_fail_expand(t_prompt *prom, char **command, char **str)
{
	ft_free_matrix(&prom->envp);
	if (command && command[0])
		ft_free_matrix(&command);
	if (str && str[0])
		ft_free_matrix(&str);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}

// remove and handle single double quotes and ~.
static char	**expand(char **args, t_prompt *prom)
{
	char	**str;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_path(args[i], -1, quotes, get_env_var("HOME",
					prom->envp, 4, prom));
		if (!args[i])
			handle_fail_expand(prom, args, str);
		str = split_separator(args[i], "<|>");
		if (!str)
			handle_fail_expand(prom, args, NULL);
		if (!ft_matrix_replace_in(&args, str, i))
			handle_fail_expand(prom, args, str);
		i = i + ft_matrixlen(str) - 1;
		ft_free_matrix(&str);
	}
	return (args);
}

static void	*parsing(char **command, t_prompt *prom)
{
	int		is_exit;
	char	**temp;

	is_exit = 0;
	temp = expand(command, prom);
	prom->cmds = make_node(temp, prom);
	if (!prom->cmds)
		return (prom);
	prom->size = ft_lstsize(prom->cmds);
	prom->exit_status = handle_built_in(prom, prom->cmds, &is_exit, command);
	while (wait(NULL) != -1)
		;
	if (command && is_exit)
	{
		ft_lstclear(&prom->cmds, free_content);
		return (NULL);
	}
	return (prom);
}

void	check_args_util(t_prompt *prom, t_node_content *node)
{
	if (prom && prom->cmds)
		node = prom->cmds->content;
	if (prom && prom->cmds && node && node->full_cmd
		&& ft_lstsize(prom->cmds) == 1)
		prom->envp = set_env_var("_",
				node->full_cmd[ft_matrixlen(node->full_cmd) - 1], prom,
				1);
	if (prom && prom->cmds)
		ft_lstclear(&prom->cmds, free_content);
}

// all solution.
void	*check_args(char *read, t_prompt *prom)
{
	char			**str;
	t_node_content	*node;

	node = NULL;
	if (!read)
		return (handle_exit_null());
	if (!read[0] || !ft_check_space(read))
	{
		free(read);
		return ("");
	}
	if (read[0] != '\0')
		add_history(read);
	read = expand_variables(prom, read);
	str = split_quote_space(read, " ", prom);
	free(read);
	if (!str)
	{
		print_error(ERR_QUO, NULL, 1, prom);
		return ("");
	}
	prom = parsing(str, prom);
	check_args_util(prom, node);
	return (prom);
}
