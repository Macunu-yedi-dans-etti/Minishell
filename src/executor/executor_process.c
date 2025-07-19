/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_and_exec(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	close_extra_fds(in_fd, out_fd);
	reset_signals();
	if (!cmd->full_cmd || !cmd->full_cmd[0] || cmd->full_cmd[0][0] == '\0')
	{
		ft_putendl_fd("minishell: empty command", 2);
		exit(0);
	}
	if (apply_redirects(cmd, req))
		exit(1);
	if (cmd->infile != STDIN_FILENO)
		set_fd(cmd->infile, STDIN_FILENO);
	else
		set_fd(in_fd, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		set_fd(cmd->outfile, STDOUT_FILENO);
	else
		set_fd(out_fd, STDOUT_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (is_builtin(cmd->full_cmd[0]))
		handle_builtin_execution(cmd, req);
	else
		handle_external_execution(cmd, req);
}

pid_t	exec_external_cmd(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		setup_and_exec(cmd, req, in_fd, out_fd);
	return (pid);
}
