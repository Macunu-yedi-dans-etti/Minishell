/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:46 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/02 14:33:10 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(char **envp, t_req *req)
{
	int	i;

	if (!envp)
	{
		ft_putendl_fd("minishell: env: environment is null", STDERR_FILENO);
		if (req)
			req->exit_stat = 1;
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	if (req)
		req->exit_stat = 0;
	return (0);
}
