/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:04 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 04:23:08 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_builtin(t_shell *cmd, t_req *req)
{
	int	ret;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		g_exit_status = 1;
		return (1);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "echo", 5))
		ret = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->full_cmd[0], "pwd", 4))
		ret = builtin_pwd();
	else if (!ft_strncmp(cmd->full_cmd[0], "env", 4))
		ret = builtin_env(req->envp);
	else if (!ft_strncmp(cmd->full_cmd[0], "cd", 3))
		ret = builtin_cd(cmd, req);
	else if (!ft_strncmp(cmd->full_cmd[0], "export", 7))
		ret = builtin_export(cmd->full_cmd, req);
	else if (!ft_strncmp(cmd->full_cmd[0], "unset", 6))
		ret = builtin_unset(cmd->full_cmd, req);
	else if (!ft_strncmp(cmd->full_cmd[0], "exit", 5))
		return builtin_exit(cmd->full_cmd);
	else
	{
		ms_error(ERR_NO_CMD, cmd->full_cmd[0], 1);
		g_exit_status = 127;
		return (127);
	}
	g_exit_status = ret;
	return (ret);
}

