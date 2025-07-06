/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:22:01 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 03:32:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		perror("");
		g_exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	g_exit_status = 0;
	return (0);
}
