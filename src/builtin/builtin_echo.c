/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:23 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 20:17:33 by haloztur         ###   ########.fr       */
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

int	builtin_echo(t_shell *cmd, t_req *req)
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
		if (cmd->full_cmd[i])
			ft_putstr_fd(cmd->full_cmd[i], STDOUT_FILENO);
		if (cmd->full_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	if (req)
		req->exit_stat = 0;
	return (0);
}
