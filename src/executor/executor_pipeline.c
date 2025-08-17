/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:21:07 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:15:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cmd_count(t_pipeline_data *data)
{
	t_cmd	*current;
	int		counter;

	if (!data->req->cmds)
		return (0);
	counter = 0;
	current = data->req->cmds;
	while (current)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}

static void	handle_single_builtin(t_pipeline_data *data)
{
	process_single_command(data);
	data->pids[data->i] = -1;
}

static void	execute_single_cmd(t_pipeline_data *data)
{
	if (!data->current_cmd)
		return ;
	handle_empty_commands(data);
	if (data->pids[data->i] != -1)
	{
		data->output_fd = setup_pipe_output(data);
		if (data->output_fd != -1)
		{
			data->real_in = setup_pipe_input(data);
			data->pids[data->i] = exec_external_cmd(data);
			handle_pipe_cleanup(data);
			if (data->current_cmd->next && data->output_fd != STDOUT_FILENO)
				data->input_fd = data->pipe_fd[0];
		}
	}
}

static void	execute_loop(t_pipeline_data *data)
{
	data->input_fd = STDIN_FILENO;
	data->i = 0;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->output_fd = -1;
	data->real_in = -1;
	data->current_cmd = data->req->cmds;
	while (data->current_cmd)
	{
		if (data->count == 1 && data->current_cmd->full_cmd
			&& is_builtin(data->current_cmd->full_cmd[0]))
			handle_single_builtin(data);
		else
			execute_single_cmd(data);
		data->i++;
		data->current_cmd = data->current_cmd->next;
	}
	wait_for_processes(data);
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
}

void	execute_cmds(t_req *req)
{
	t_pipeline_data	data;

	data.req = req;
	data.count = cmd_count(&data);
	if (data.count <= 0 || data.count > 1024)
	{
		req->exit_stat = 1;
		return ;
	}
		data.pids = (pid_t *)malloc(sizeof(pid_t) * data.count);
		if (!data.pids)
		{
				req->exit_stat = 1;
				return ;
		}
	ft_memset(data.pids, 0, sizeof(pid_t) * data.count);
	execute_loop(&data);
	ft_memset(data.pids, 0, sizeof(pid_t) * data.count);
		free(data.pids);
}
