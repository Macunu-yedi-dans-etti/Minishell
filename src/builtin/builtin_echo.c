/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:23 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 02:40:07 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_shell *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->full_cmd[i] && is_valid_n_flag(cmd->full_cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->full_cmd[i])
	{
		ft_putstr_fd(cmd->full_cmd[i], STDOUT_FILENO);
		if (cmd->full_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 0;
	return (0);
}
