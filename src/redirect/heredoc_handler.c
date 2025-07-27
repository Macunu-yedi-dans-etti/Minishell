/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:45:10 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/27 13:44:17 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	_exit(130);
}

static int do_heredoc_child(const char *delimiter, int pipe_fd[2])
{
	char *line;

	signal(SIGINT, heredoc_sigint_handler);
	close(pipe_fd[0]);

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(pipe_fd[1]);
			_exit(130);
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int handle_heredoc(const char *delimiter, t_req *req)
{
	int pipe_fd[2];
	pid_t pid;
	int status;
	void (*old_sigint)(int);

	old_sigint = signal(SIGINT, SIG_IGN);
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		if (req)
			req->exit_stat = 1;
		signal(SIGINT, old_sigint);
		return -1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (req)
			req->exit_stat = 1;
		signal(SIGINT, old_sigint);
		return -1;
	}

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		do_heredoc_child(delimiter, pipe_fd);
	}

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (req)
			req->exit_stat = 130;
		close(pipe_fd[0]);
		return -1;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		if (req)
			req->exit_stat = WEXITSTATUS(status);
		close(pipe_fd[0]);
		return -1;
	}
	return pipe_fd[0];
}

