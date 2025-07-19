/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_builtin_io(t_shell *cmd, int input_fd, int *backup_in,
							int *backup_out)
{
	if (cmd->infile == STDIN_FILENO && input_fd != STDIN_FILENO)
	{
		*backup_in = dup(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	else if (cmd->infile != STDIN_FILENO)
	{
		*backup_in = dup(STDIN_FILENO);
		dup2(cmd->infile, STDIN_FILENO);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		*backup_out = dup(STDOUT_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
	}
}

void	exec_single_builtin(t_shell *cmd, t_req *req, int input_fd)
{
	int	backup_out;
	int	backup_in;

	backup_out = -1;
	backup_in = -1;
	if (!cmd->full_cmd || !cmd->full_cmd[0])
	{
		req->exit_stat = 0;
		return ;
	}
	if (apply_redirects(cmd, req))
	{
		req->exit_stat = 1;
		return ;
	}
	setup_builtin_io(cmd, input_fd, &backup_in, &backup_out);
	run_builtin(cmd, req);
	restore_io(&backup_in, &backup_out);
}
