/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:06:45 by salam             #+#    #+#             */
/*   Updated: 2025/02/20 20:14:24 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char **read, char **path, t_prompt *prom)
{
	*path = getcwd(NULL, 0);
	*read = ft_strjoin("\033[34m", *path);
	if (!*read)
	{
		free(*path);
		ft_free_matrix(&prom->envp);
		print_error(ALLOC, NULL, 1, prom);
		exit(1);
	}
	free(*path);
	*path = ft_strjoin_gnl(*read, ">\033[0m ");
	if (!*path)
	{
		ft_free_matrix(&prom->envp);
		print_error(ALLOC, NULL, 1, prom);
		exit(1);
	}
}
