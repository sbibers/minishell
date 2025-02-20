/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:53:24 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_content	*init_node_content(void)
{
	t_node_content	*cont;

	cont = malloc(sizeof(t_node_content));
	if (!cont)
		return (NULL);
	cont->full_cmd = NULL;
	cont->full_path = NULL;
	cont->in = 0;
	cont->out = 1;
	return (cont);
}

// put infile and outfile for every command.
// put the command in the content of the node.
// str[0] : with single and double quotes.
// str[1] = without single and double quotes.
t_node_content	*put_content_2_node(t_node_content *node,
char **str[2], int *i, t_prompt *prom)
{
	if (str[0][*i])
	{
		if (str[0][*i][0] == '>' && str[0][*i + 1] && str[0][*i + 1][0] == '>')
			node = out_redirction_double(node, str[1], i, prom);
		else if (str[0][*i][0] == '>')
			node = out_redirction_single(node, str[1], i, prom);
		else if (str[0][*i][0] == '<' && str[0][*i + 1] && str[0][*i
				+ 1][0] == '<')
			node = herdoc(node, str[1], i, prom);
		else if (str[0][*i][0] == '<')
			node = in_redirection(node, str[1], i, prom);
		else if (str[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, str[1][*i]);
		else
		{
			print_error(SYN_PIP, NULL, 2, prom);
			*i = -2;
		}
		return (node);
	}
	print_error(SYN_PIP, NULL, 2, prom);
	*i = -2;
	return (node);
}

char	**allocate_and_dup_args(char **args, t_prompt *prom)
{
	char	**temp;

	temp = ft_dup_matrix(args);
	if (!temp)
	{
		ft_free_matrix(&args);
		ft_free_matrix(&prom->envp);
		print_error(ALLOC, NULL, 1, prom);
		exit(1);
	}
	return (temp);
}

void	trim_args(char **temp, char **args, t_prompt *prom)
{
	char	*str;
	int		j;

	j = -1;
	while (temp && temp[++j])
	{
		str = delete_qoutes(temp[j], 0, 0);
		if (!str)
		{
			ft_free_matrix(&temp);
			ft_free_matrix(&args);
			ft_free_matrix(&prom->envp);
			print_error(ALLOC, NULL, 1, prom);
			exit(1);
		}
		free(temp[j]);
		temp[j] = str;
	}
}
