/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:46 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 02:49:51 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
	{
		ft_putendl_fd("minishell: env: environment is null", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	g_exit_status = 0;
	return (0);
}
