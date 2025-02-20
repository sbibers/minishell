/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:59:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

static int	handle_herdoc_util(char *temp, char *str[2], t_prompt *prom)
{
	temp = str[1];
	str[1] = ft_strjoin(str[1], str[0]);
	free(temp);
	free(str[0]);
	str[0] = readline("> ");
	if (g_e_status == SIGINT)
	{
		printf("\n");
		prom->exit_status = 130;
		prom->flag = 1;
		return (1);
	}
	return (0);
}

static int	handle_herdoc_util_2(char *temp, char *str[2], int messi)
{
	temp = str[0];
	str[0] = ft_strjoin(str[0], "\n");
	if (!str[0])
	{
		dup2(messi, STDIN_FILENO);
		close(messi);
		free(temp);
		free(str[0]);
		return (1);
	}
	free(temp);
	return (0);
}

static void	handle_herdoc_util_3(char *str[2], int messi)
{
	dup2(messi, STDIN_FILENO);
	close(messi);
	free(str[0]);
	rl_replace_line("", 0);
	rl_on_new_line();
}

char	*get_here_str(char *str[2], char *limit, char *warn, t_prompt *prom)
{
	char	*temp;
	int		in_file;
	size_t	len;

	len = 0;
	temp = NULL;
	in_file = dup(STDIN_FILENO);
	signal(SIGINT, change_sigint);
	while (g_e_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len)
			|| ft_strlen(limit) != len))
	{
		if (handle_herdoc_util(temp, str, prom))
			break ;
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		if (handle_herdoc_util_2(temp, str, in_file))
			return (NULL);
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	handle_herdoc_util_3(str, in_file);
	return (str[1]);
}

int	handle_herdoc(char *str[2], char *temp[2], t_prompt *prom)
{
	int	pipes[2];

	signal(SIGINT, SIG_DFL);
	g_e_status = 0;
	if (pipe(pipes) == -1)
	{
		print_error(PIPE_ERR, NULL, 1, prom);
		return (-1);
	}
	str[1] = get_here_str(str, temp[0], temp[1], prom);
	write(pipes[1], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(pipes[1]);
	if (g_e_status == 130)
	{
		signal(SIGINT, &handle_sigint);
		close(pipes[0]);
		return (-1);
	}
	signal(SIGINT, &handle_sigint);
	return (pipes[0]);
}
