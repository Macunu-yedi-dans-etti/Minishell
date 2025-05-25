
#include "../minishell.h"

void exec_cmds(t_cmd *cmds, char ***env)
{
 	char *path;
	int fd_in, fd_out;
	pid_t pid;

	while (cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			// <
			if (cmds->redir_in)
			{
				fd_in = open(cmds->redir_in, O_RDONLY);
				if (fd_in == -1)
				{
					perror("minishell: infile");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}

			// >
			if (cmds->redir_out)
			{
				fd_out = open(cmds->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out == -1)
				{
					perror("minishell: outfile");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}

			// >>
			if (cmds->redir_append)
			{
				fd_out = open(cmds->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_out == -1)
				{
					perror("minishell: append file");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}

			// fonksiyonlar
			if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
				exit(build_exit(cmds->args));
			else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
				exit(command_export(env, cmds->args));
			else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
				exit(command_unset(env, cmds->args));
			else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
				exit(builtin_env(*env));

			// Dış komut
			path = paths(cmds->args[0], *env);
			if (!path)
			{
				ft_putstr_fd("minishell: command not found: ", 2);
				ft_putendl_fd(cmds->args[0], 2);
				exit(127);
			}
			execve(path, cmds->args, *env);
			perror("execve");
			exit(1);
		}
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
		}
		else
		{
			perror("minishell: fork failed");
		}

		cmds = cmds->next;
	}
}

