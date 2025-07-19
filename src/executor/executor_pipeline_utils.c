/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:21:01 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:21:01 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_execution(t_list *cmds, pid_t **pids, t_req *req)
{
	int	count;

	count = ft_lstsize(cmds);
	*pids = ft_calloc(count, sizeof(pid_t));
	if (!*pids)
	{
		perror("malloc");
		req->exit_stat = 1;
		return (-1);
	}
	return (count);
}

int	setup_pipe_output(t_list *node, t_shell *cmd, int *pipe_fd)
{
	int	output_fd;

	output_fd = STDOUT_FILENO;
	if (node->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		output_fd = pipe_fd[1];
	}
	else if (cmd->outfile != STDOUT_FILENO)
		output_fd = cmd->outfile;
	return (output_fd);
}

int	setup_pipe_input(t_shell *cmd, int input_fd)
{
	int	real_in;

	real_in = input_fd;
	if (cmd->infile != STDIN_FILENO)
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		real_in = cmd->infile;
	}
	return (real_in);
}

void	handle_pipe_cleanup(int real_in, int input_fd, int output_fd,
	t_list *node)
{
	if (real_in != STDIN_FILENO && real_in != input_fd)
		close(real_in);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (node->next && output_fd != STDOUT_FILENO)
		close(output_fd);
}
