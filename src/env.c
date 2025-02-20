/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:41:03 by sbibers           #+#    #+#             */
/*   Updated: 2025/02/20 20:04:28 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_e_status;

static void	stop_get(char **envp, t_prompt *prom)
{
	ft_free_matrix(&envp);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}

char	*get_env_var(char *var, char **envp, int n, t_prompt *prom)
{
	int		i;
	int		n2;
	char	*sub;

	i = 0;
	if (ft_strncmp(var, "?", 1) == 0 && ft_strlen(var) == 1)
		return (ft_itoa(prom->exit_status));
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_index(envp[i], '='))
			n2 = ft_strchr_index(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
		{
			sub = ft_substr(envp[i], n2 + 1, ft_strlen(envp[i]));
			if (!sub)
				stop_get(envp, prom);
			return (sub);
		}
		i++;
	}
	return (NULL);
}

static void	stop_set(char *value, char **envp, char *new_entry, t_prompt *prom)
{
	if (envp && envp[0])
		ft_free_matrix(&envp);
	if (value)
		free(value);
	if (new_entry)
		free(new_entry);
	print_error(ALLOC, NULL, 1, prom);
	exit(1);
}

static char	**set_env_util(t_set_env *set_env, char **envp, char *var)
{
	set_env->equal_pos = ft_strchr(envp[set_env->i], '=');
	if (set_env->equal_pos && !ft_strncmp(envp[set_env->i], var,
			set_env->equal_pos - envp[set_env->i]))
	{
		free(envp[set_env->i]);
		envp[set_env->i] = set_env->new_entry;
		return (envp);
	}
	return (NULL);
}

// add to env if not exist, if exist edit it.
char	**set_env_var(char *var, char *value, t_prompt *prom, int n)
{
	t_set_env	set_env;

	if (n < 0)
		n = ft_strlen(var);
	set_env.add_equal = ft_strjoin(var, "=");
	if (!set_env.add_equal)
		stop_set(value, prom->envp, NULL, prom);
	set_env.new_entry = ft_strjoin(set_env.add_equal, value);
	free(set_env.add_equal);
	if (!set_env.new_entry)
		stop_set(value, prom->envp, NULL, prom);
	set_env.i = 0;
	while (prom->envp && prom->envp[set_env.i])
	{
		if (set_env_util(&set_env, prom->envp, var))
			return (prom->envp);
		set_env.i++;
	}
	prom->envp = ft_extend_matrix(prom->envp, set_env.new_entry);
	if (!prom->envp)
		stop_set(NULL, NULL, set_env.new_entry, prom);
	free(set_env.new_entry);
	return (prom->envp);
}
