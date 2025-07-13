/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:04 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 12:02:26 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_builtin(t_shell *cmd, t_req *req)
{
	if (!ft_strncmp(cmd->full_cmd[0], "echo", 5))
		return (builtin_echo(cmd));
	else if (!ft_strncmp(cmd->full_cmd[0], "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd->full_cmd[0], "env", 4))
		return (builtin_env(req->envp));
	else if (!ft_strncmp(cmd->full_cmd[0], "cd", 3))
		return (builtin_cd(cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "export", 7))
		return (builtin_export(cmd->full_cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "unset", 6))
		return (builtin_unset(cmd->full_cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "exit", 5))
		return (builtin_exit(cmd->full_cmd));
	else
		return (-1);
}

int	run_builtin(t_shell *cmd, t_req *req)
{
	int	ret;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		g_exit_status = 1;
		return (1);
	}
	ret = handle_builtin(cmd, req);
	if (ret == -1)
	{
		ms_error(ERR_NO_CMD, cmd->full_cmd[0], 1);
		g_exit_status = 127;
		return (127);
	}
	g_exit_status = ret;
	return (ret);
}
