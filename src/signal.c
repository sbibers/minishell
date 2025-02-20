/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:00:07 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/19 18:09:31 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_e_status;

void	handle_sigint(int sig)
// handle ctrl + c.
{
	if (sig == SIGINT)
	{
		g_e_status = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	change_sigint(int sig)
{
	(void)sig;
	g_e_status = SIGINT;
	close(STDIN_FILENO);
}
