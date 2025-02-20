/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:26:04 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:14:20 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_e_status;

void	fail_allocate(t_prompt *prom, int flag)
{
	ft_free_matrix(&prom->envp);
	print_error(flag, NULL, 1, prom);
	exit(1);
}

// init variables and get the path of the minishell.
// SHILVL : how much shell open.
static void	init_vars(t_prompt *prom, char *str, char **argv)
{
	char	*sstr;

	str = getcwd(NULL, 0);
	prom->envp = set_env_var("PWD", str, prom, 3);
	free(str);
	str = get_env_var("SHLVL", prom->envp, 5, prom);
	if (!str || ft_atoi(str) <= 0)
		sstr = ft_strdup("1");
	else
		sstr = ft_itoa(ft_atoi(str) + 1);
	free(str);
	if (!sstr)
		fail_allocate(prom, ALLOC);
	prom->envp = set_env_var("SHLVL", sstr, prom, 5);
	free(sstr);
	str = get_env_var("PATH", prom->envp, 4, prom);
	if (!str)
		prom->envp = set_env_var("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prom, 4);
	free(str);
	str = get_env_var("_", prom->envp, 1, prom);
	if (!str)
		prom->envp = set_env_var("_", argv[0], prom, 1);
	free(str);
}

static void	check_tty_or_stop_program(int flag, char **envp, int exit_status)
{
	if (flag == 1)
	{
		if (!isatty(0) || !isatty(1) || !isatty(2))
			exit(1);
	}
	else
	{
		ft_free_matrix(&envp);
		clear_history();
		exit(exit_status);
	}
}

// init env and all the struct.
static void	init_prompt(t_prompt *prom, char **argv, char **envp)
{
	char	*str;

	check_tty_or_stop_program(1, NULL, 1);
	str = NULL;
	prom->cmds = NULL;
	prom->envp = NULL;
	prom->size = 0;
	prom->envp = ft_dup_matrix(envp);
	if (!prom->envp)
	{
		print_error(ALLOC, NULL, 1, prom);
		exit(1);
	}
	prom->exit_status = 0;
	init_vars(prom, str, argv);
}

int	main(int argc, char **argv, char **envp)
{
	char		*read;
	t_prompt	prom;
	char		*path;

	init_prompt(&prom, argv, envp);
	while (argc && argv)
	{
		prom.flag = 0;
		g_e_status = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		path = NULL;
		get_path(&read, &path, &prom);
		read = readline(path);
		free(path);
		if (g_e_status == SIGINT)
			prom.exit_status = 130;
		if (!check_args(read, &prom))
			check_tty_or_stop_program(0, prom.envp, prom.exit_status);
	}
	ft_free_matrix(&prom.envp);
	clear_history();
	return (prom.exit_status);
}
