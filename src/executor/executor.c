#include "../../minishell.h"

static void exec_external_cmd(t_shell *cmd, t_req *req, int input_fd, int output_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (apply_redirects(cmd))
			exit(EXIT_FAILURE);

		if (cmd->infile != STDIN_FILENO)
			dup2(cmd->infile, STDIN_FILENO);
		else if (input_fd != STDIN_FILENO)
			dup2(input_fd, STDIN_FILENO);

		if (cmd->outfile != STDOUT_FILENO)
			dup2(cmd->outfile, STDOUT_FILENO);
		else if (output_fd != STDOUT_FILENO)
			dup2(output_fd, STDOUT_FILENO);

		execve(cmd->full_path, cmd->full_cmd, req->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

void execute_cmds(t_list *cmds, t_req *req)
{
	t_list	*node;
	int		pipe_fd[2];
	int		input_fd;

	input_fd = STDIN_FILENO;
	node = cmds;
	while (node)
	{
		t_shell *cmd = (t_shell *)node->content;

		if (is_builtin(cmd->full_cmd[0]) && !node->next)
		{
			if (apply_redirects(cmd) == 0)
			{
				int backup_stdout = -1;
				int backup_stdin = -1;

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
				fprintf(stderr, "Redirection failed\n");
		}
		else
		{
			if (node->next)
				pipe(pipe_fd);
			exec_external_cmd(cmd, req, input_fd,
				node->next ? pipe_fd[1] : STDOUT_FILENO);
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