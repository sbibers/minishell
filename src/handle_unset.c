/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:59:13 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_unset_2(int j, t_prompt *prom, char **args, t_list *cmd)
{
	if (!ft_matrix_replace_in(&prom->envp, NULL, j))
	{
		stop_make_node(cmd, args, prom->envp);
		print_error(ALLOC, NULL, 1, prom);
		exit(1);
	}
}

static void	handle_unset_1(t_list *cmd, char **args, t_prompt *prom)
{
	stop_make_node(cmd, args, prom->envp);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}

int	handle_unset(t_prompt *prom, t_list *cmd, char **args)
{
	t_unset	var;

	var.i = 0;
	var.argv = ((t_node_content *)prom->cmds->content)->full_cmd;
	if (ft_matrixlen(var.argv) >= 2)
	{
		while (var.argv[++var.i])
		{
			if (var.argv[var.i][ft_strlen(var.argv[var.i]) - 1] != '=')
			{
				var.temp = ft_strjoin(var.argv[var.i], "=");
				if (!var.temp)
					handle_unset_1(cmd, args, prom);
				free(var.argv[var.i]);
				var.argv[var.i] = var.temp;
			}
			if (found_var(var.argv[var.i], prom->envp, &var.j))
				handle_unset_2(var.j, prom, args, cmd);
		}
	}
	return (0);
}
