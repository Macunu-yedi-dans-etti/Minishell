/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:04 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:23:08 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_builtin(t_shell *cmd, t_req *req)
{
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "echo", 5))
		return (builtin_echo(cmd));
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->full_cmd[0], "env", 4))
		return (builtin_env(req->envp));
	if (!ft_strncmp(cmd->full_cmd[0], "cd", 3))
		return (builtin_cd(cmd, req));
	if (!ft_strncmp(cmd->full_cmd[0], "export", 7))
		return (builtin_export(cmd->full_cmd, req));
	if (!ft_strncmp(cmd->full_cmd[0], "unset", 6))
		return (builtin_unset(cmd->full_cmd, req));
	if (!ft_strncmp(cmd->full_cmd[0], "exit", 5))
		return (builtin_exit(cmd->full_cmd));
	return (1);
}
