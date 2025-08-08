/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:21:07 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:21:07 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_single_builtin(t_list *cmds, t_req *req, pid_t *pids, int i)
{
	process_single_command(cmds, req, STDIN_FILENO);
	pids[i] = -1;
}

static void	execute_single_cmd(t_list *node, t_cmd *cmd,
	t_pipeline_data *data, t_req *req)
{
	pid_t	*pids;

	pids = data->pids;
	handle_empty_commands(cmd, req, pids, data->i);
	if (pids[data->i] != -1)
	{
		data->output_fd = setup_pipe_output(node, cmd, data->pipe_fd);
		if (data->output_fd != -1)
		{
			data->real_in = setup_pipe_input(cmd, data->input_fd);
			pids[data->i] = exec_external_cmd(cmd, req, data->real_in,
					data->output_fd);
			handle_pipe_cleanup(data->real_in, data->input_fd,
				data->output_fd, node);
			if (node->next && data->output_fd != STDOUT_FILENO)
				data->input_fd = data->pipe_fd[0];
		}
	}
}

static void	execute_loop(t_list *cmds, pid_t *pids, int count, t_req *req)
{
	t_list			*node;
	t_cmd			*cmd;
	t_pipeline_data	data;

	data.input_fd = STDIN_FILENO;
	data.i = 0;
	data.pids = pids;
	data.pipe_fd[0] = -1;
	data.pipe_fd[1] = -1;
	data.output_fd = -1;
	data.real_in = -1;
	node = cmds;
	while (node)
	{
		cmd = (t_cmd *)node->content;
		if (count == 1 && cmd->full_cmd && is_builtin(cmd->full_cmd[0]))
			handle_single_builtin(cmds, req, pids, data.i);
		else
			execute_single_cmd(node, cmd, &data, req);
		data.i++;
		node = node->next;
	}
	wait_for_processes(pids, count, req);
	if (data.input_fd != STDIN_FILENO)
		close(data.input_fd);
}

void	execute_cmds(t_list *cmds, t_req *req)
{
	pid_t	pids_stack[64];  // Stack array - no malloc needed!
	pid_t	*pids;
	int		count;

	count = ft_lstsize(cmds);
	if (count <= 0 || count > 1024)
	{
		req->exit_stat = 1;
		return ;
	}
	// Use stack array instead of heap
	pids = pids_stack;
	memset(pids, 0, sizeof(pid_t) * count);
	execute_loop(cmds, pids, count, req);
	// No need to free stack array - it's automatic!
	// Just clear the values for good measure
	memset(pids, 0, sizeof(pid_t) * count);
}
