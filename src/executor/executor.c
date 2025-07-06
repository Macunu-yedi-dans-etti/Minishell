/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:33 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 04:00:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_and_exec(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	if (apply_redirects(cmd))
		exit(1);
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	else if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	if (!cmd->full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->full_cmd && cmd->full_cmd[0]
			? cmd->full_cmd[0] : "(null)", 2);
		exit(127);
	}
	execve(cmd->full_path, cmd->full_cmd, req->envp);
	perror("execve");
	exit(1);
}

static void	exec_external_cmd(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		setup_and_exec(cmd, req, in_fd, out_fd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

static void	exec_single_builtin(t_shell *cmd, t_req *req)
{
	int	backup_stdout;
	int	backup_stdin;

	backup_stdout = -1;
	backup_stdin = -1;
	if (apply_redirects(cmd) == 0)
	{
		if (cmd->outfile != STDOUT_FILENO)
		{
			backup_stdout = dup(STDOUT_FILENO);
			dup2(cmd->outfile, STDOUT_FILENO);
		}
		if (cmd->infile != STDIN_FILENO)
		{
			backup_stdin = dup(STDIN_FILENO);
			dup2(cmd->infile, STDIN_FILENO);
		}
		run_builtin(cmd, req);
		if (backup_stdout != -1)
		{
			dup2(backup_stdout, STDOUT_FILENO);
			close(backup_stdout);
		}
		if (backup_stdin != -1)
		{
			dup2(backup_stdin, STDIN_FILENO);
			close(backup_stdin);
		}
	}
	else
	{
		ft_putendl_fd("minishell: redirection failed", 2);
		g_exit_status = 1;
	}
}

void	execute_cmds(t_list *cmds, t_req *req)
{
	t_list	*node;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	t_shell	*cmd;

	node = cmds;
	input_fd = STDIN_FILENO;
	while (node)
	{
		cmd = (t_shell *)node->content;
		if (is_builtin(cmd->full_cmd[0]) && !node->next)
			exec_single_builtin(cmd, req);
		else
		{
			if (node->next)
			{
				if (pipe(pipe_fd) == -1)
				{
					perror("pipe");
					return ;
				}
				output_fd = pipe_fd[1];
			}
			else
				output_fd = STDOUT_FILENO;
			exec_external_cmd(cmd, req, input_fd, output_fd);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (node->next)
			{
				close(pipe_fd[1]);
				input_fd = pipe_fd[0];
			}
		}
		node = node->next;
	}
}
