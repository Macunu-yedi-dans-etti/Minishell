/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_builtin_execution(t_shell *cmd, t_req *req)
{
	int	devnull;

	devnull = open("/dev/null", O_RDONLY);
	if (devnull != -1)
	{
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	run_builtin(cmd, req);
	exit(req->exit_stat);
}

static void	handle_execve_error(t_shell *cmd, t_req *req)
{
	if (errno == EISDIR)
		ms_error(ERR_IS_DIR, cmd->full_path, 126, req);
	else if (errno == EACCES)
	{
		if (access(cmd->full_path, X_OK) == 0)
			ms_error(ERR_IS_DIR, cmd->full_path, 126, req);
		else
			ms_error(ERR_NO_PERM, cmd->full_path, 126, req);
	}
	else if (errno == ENOENT)
		ms_error(ERR_NO_CMD, cmd->full_path, 127, req);
	else
	{
		perror("execve");
		req->exit_stat = 1;
	}
}

void	handle_external_execution(t_shell *cmd, t_req *req)
{
	if (!cmd->full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (cmd->full_cmd && cmd->full_cmd[0])
			ft_putendl_fd(cmd->full_cmd[0], 2);
		else
			ft_putendl_fd("(null)", 2);
		exit(127);
	}
	execve(cmd->full_path, cmd->full_cmd, req->envp);
	handle_execve_error(cmd, req);
	exit(req->exit_stat);
}
