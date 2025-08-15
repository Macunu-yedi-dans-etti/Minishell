/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_empty_commands(t_pipeline_data *data)
{
	if (!data->current_cmd || !data->current_cmd->full_cmd
		|| !data->current_cmd->full_cmd[0])
	{
		data->req->exit_stat = 0;
		data->pids[data->i] = -1;
		return ;
	}
	if (data->current_cmd->full_cmd[0][0] == '\0')
	{
		data->req->exit_stat = 0;
		data->pids[data->i] = -1;
		return ;
	}
}

void	process_single_command(t_pipeline_data *data)
{
	if (data->current_cmd && data->current_cmd->full_cmd
		&& is_builtin(data->current_cmd->full_cmd[0]))
		exec_single_builtin(data);
}

void	wait_for_processes(t_pipeline_data *data)
{
	int	status;
	int	i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	i = 0;
	while (i < data->count)
	{
		if (data->pids[i] > 0)
		{
			waitpid(data->pids[i], &status, 0);
			if (WIFEXITED(status))
				data->req->exit_stat = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->req->exit_stat = 128 + WTERMSIG(status);
		}
		i++;
	}
	setup_signals(data->req);
}
