/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_exec(t_shell *cmd, t_req *req, int *input_fd, pid_t *pid)
{
	int	real_in;

	real_in = *input_fd;
	if (cmd->infile != STDIN_FILENO)
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		real_in = cmd->infile;
	}
	*pid = exec_external_cmd(cmd, req, real_in, STDOUT_FILENO);
	if (real_in != STDIN_FILENO)
		close(real_in);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	return (0);
}

void	handle_empty_commands(t_shell *cmd, t_req *req, pid_t *pids, int i)
{
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		req->exit_stat = 0;
		pids[i] = -1;
		return ;
	}
	if (cmd->full_cmd[0][0] == '\0')
	{
		req->exit_stat = 0;
		pids[i] = -1;
		return ;
	}
}

void	process_single_command(t_list *cmds, t_req *req, int input_fd)
{
	t_shell	*cmd;

	cmd = (t_shell *)cmds->content;
	if (is_builtin(cmd->full_cmd[0]))
		exec_single_builtin(cmd, req, input_fd);
}

void	wait_for_processes(pid_t *pids, int count, t_req *req)
{
	int	i;
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				req->exit_stat = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				req->exit_stat = 128 + WTERMSIG(status);
		}
		i++;
	}
	setup_signals();
}
