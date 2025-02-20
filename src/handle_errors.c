/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:41:34 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static int	check_number_exit(const char *str, int *num)
{
	int		neg;

	neg = 1;
	*num = 0;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		neg = -neg;
	if (*str == '-' || *str == '+')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*num = 10 * *num + (*str - '0');
		str++;
	}
	if (*str && !((*str == ' ') || (*str >= 9 && *str <= 13)))
		return (-1);
	*num *= neg;
	return (0);
}

static void	handle_print_exit(t_node_content *node)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(node->full_cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

// handle the command exit.
// status_arr[0] = status_arr[0] % 256 + 256 * (status_arr[0] < 0) : over flow.
int	handle_exit(t_list *cmd, int *exit_num, t_prompt *prom)
{
	t_node_content	*node;
	int				status_num[2];

	node = cmd->content;
	*exit_num = (!cmd->next && (prom->size == 1));
	if (*exit_num)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status_num[1] = check_number_exit(node->full_cmd[1], &status_num[0]);
	if (status_num[1] == -1)
	{
		handle_print_exit(node);
		return (2);
	}
	else if (node->full_cmd[2])
	{
		*exit_num = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status_num[0] = status_num[0] % 256 + 256 * (status_num[0] < 0);
	return (status_num[0]);
}

void	check_cd(char **str[2], t_prompt *prom)
// handle cd.
{
	DIR	*directory;

	directory = NULL;
	if (str[0][1])
		directory = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_e_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_e_status = chdir(str[1][0]) == -1;
	if (str[0][1] && directory && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		print_error(ERR_NODIR, str[0][1], 1, prom);
	else if (str[0][1])
		print_error(NOT_DIR, str[0][1], 1, prom);
	if (str[0][1] && directory)
		closedir(directory);
}

void	free_content(void *content)
// free the content of the node(full_cmd, full_path).
{
	t_node_content	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->in > 0)
		close(node->in);
	if (node->out > 1)
		close(node->out);
	free(node);
}
