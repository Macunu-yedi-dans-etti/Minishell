/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:23:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:23:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	setup_pipe_output(t_pipeline_data *data)
{
	int	output_fd;

	output_fd = STDOUT_FILENO;
	if (data->current_cmd->next)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			perror("minishell: pipe");
			free_cmds(data->current_cmd);
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
