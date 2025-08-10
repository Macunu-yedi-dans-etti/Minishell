/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:21:01 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cmd_count(t_cmd *cmds)
{
	int c = 0;
	while (cmds)
	{
		c++;
		cmds = cmds->next;
	}
	return (c);
}

int	init_execution(t_cmd *cmds, pid_t **pids, t_req *req)
{
	int	count;

	count = cmd_count(cmds);
	if (count <= 0 || count > 1024)
	{
		req->exit_stat = 1;
		return (-1);
	}
	*pids = ft_calloc(count, sizeof(pid_t));
	if (!*pids)
	{
		*pids = NULL;
		perror("malloc");
		req->exit_stat = 1;
		return (-1);
	}
	return (count);
}

int	setup_pipe_output(t_pipeline_data *data)
{
	int	output_fd;

	output_fd = STDOUT_FILENO;
	if (data->current_cmd->next)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			perror("minishell: pipe");
			free_cmds(data->current_cmd); // free remaining chain starting here
			return (-1);
		}
		output_fd = data->pipe_fd[1];
	}
	else if (data->current_cmd->outfile != STDOUT_FILENO)
		output_fd = data->current_cmd->outfile;
	return (output_fd);
}

int	setup_pipe_input(t_pipeline_data *data)
{
	int	real_in;

	real_in = data->input_fd;
	if (data->current_cmd->infile != STDIN_FILENO)
	{
		if (data->input_fd != STDIN_FILENO)
			close(data->input_fd);
		real_in = data->current_cmd->infile;
	}
	return (real_in);
}

void	handle_pipe_cleanup(t_pipeline_data *data)
{
	if (data->real_in != STDIN_FILENO && data->real_in != data->input_fd)
		close(data->real_in);
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	if (data->current_cmd->next && data->output_fd != STDOUT_FILENO)
		close(data->output_fd);
}
