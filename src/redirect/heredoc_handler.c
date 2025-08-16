/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:45:10 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/16 22:58:05 by haloztur         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

static char	*expand_line(char *line, t_req *req)
{
	int		i;
	char	*expanded;
	char	*tmp;
	char	*new_exp;
	char	c[2];

	i = 0;
	expanded = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = expand_token_var(line, &i, req);
			new_exp = ft_strjoin(expanded, tmp);
			free(expanded);
			free(tmp);
			expanded = new_exp;
		}
		else
		{
			c[0] = line[i++];
			c[1] = '\0';
			new_exp = ft_strjoin(expanded, c);
			free(expanded);
			expanded = new_exp;
		}
	}
	return (expanded);
}

static void	do_heredoc_child(const char *delimiter, int pipe_fd[2], t_req *req)
{
	char	*line;
	char	*expanded;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			(free_cmd(req->cur_cmd), free_cmd(req->cmds), free_req(req),
				close(pipe_fd[1]), exit(130));
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			return (free(line), close(pipe_fd[1]),
				(free_cmd(req->cur_cmd), free_cmd(req->cmds), free_req(req)),
				exit(0));
		expanded = expand_line(line, req);
		write(pipe_fd[1], expanded, ft_strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		free(expanded);
		free(line);
	}
}

int	handle_heredoc(const char *delimiter, t_req *req)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	void	(*old_sigint)(int);

	if (req && req->heredoc_interrupted)
		return (-1);
	old_sigint = signal(SIGINT, SIG_IGN);
	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), req->exit_stat = 1,
			signal(SIGINT, old_sigint), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), close(pipe_fd[0]), close(pipe_fd[1]),
			req->exit_stat = 1, signal(SIGINT, old_sigint), -1);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint_handler);
		do_heredoc_child(delimiter, pipe_fd, req);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		return (req->exit_stat = 130, req->heredoc_interrupted = 1,
			close(pipe_fd[0]), -1);
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (req->exit_stat = WEXITSTATUS(status), close(pipe_fd[0]), -1);
	return (pipe_fd[0]);
}
