/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:04 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 19:20:25 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_builtin(t_shell *cmd, t_req *req)
{
	if (!ft_strncmp(cmd->full_cmd[0], "echo", 5))
		return (builtin_echo(cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "pwd", 4))
		return (builtin_pwd(req));
	else if (!ft_strncmp(cmd->full_cmd[0], "env", 4))
		return (builtin_env(req->envp, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "cd", 3))
		return (builtin_cd(cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "export", 7))
		return (builtin_export(cmd->full_cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "unset", 6))
		return (builtin_unset(cmd->full_cmd, req));
	else if (!ft_strncmp(cmd->full_cmd[0], "exit", 5))
		return (builtin_exit(cmd->full_cmd, req));
	else
		return (-1);
}

int	run_builtin(t_shell *cmd, t_req *req)
{
	int	ret;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		req->exit_stat = 1;
		return (1);
	}
	ret = handle_builtin(cmd, req);
	if (ret == -1)
	{
		ms_error(ERR_NO_CMD, cmd->full_cmd[0], 1, req);
		req->exit_stat = 127;
		return (127);
	}
	req->exit_stat = ret;
	return (ret);
}
