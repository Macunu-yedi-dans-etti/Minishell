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

void	handle_builtin_execution(t_pipeline_data *data)
{
	int				devnull;

	devnull = open("/dev/null", O_RDONLY);
	if (devnull != -1)
	{
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	data->input_fd = STDIN_FILENO;
	run_builtin(data);
	free_all(data);
	exit(data->req->exit_stat);
}

static void	handle_execve_error(t_pipeline_data *data)
{
	if (errno == EISDIR)
		ms_error(ERR_IS_DIR, data->current_cmd->full_path, 126, data->req);
	else if (errno == EACCES)
	{
		if (access(data->current_cmd->full_path, X_OK) == 0)
			ms_error(ERR_IS_DIR, data->current_cmd->full_path, 126, data->req);
		else
			ms_error(ERR_NO_PERM, data->current_cmd->full_path, 126, data->req);
	}
	else if (errno == ENOENT)
		ms_error(ERR_NO_CMD, data->current_cmd->full_path, 127, data->req);
	else
	{
		perror("execve");
		data->req->exit_stat = 1;
	}
	free_all(data);
}

void	handle_external_execution(t_pipeline_data *data)
{
	if (!data->current_cmd->full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (data->current_cmd->full_cmd && data->current_cmd->full_cmd[0])
		{
			ft_putendl_fd(data->current_cmd->full_cmd[0], 2);
		}
		else
			ft_putendl_fd("(null)", 2);
		free_all(data);
		exit(127);
	}
	execve(data->current_cmd->full_path, data->current_cmd->full_cmd,
		data->req->envp);
	handle_execve_error(data);
	exit(data->req->exit_stat);
}
