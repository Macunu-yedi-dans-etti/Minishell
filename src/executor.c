#include "../minishell.h"

void exec_cmds(t_cmd *cmds, char ***env)
{
    int     pipefd[2];
    int     prev_fd = -1;
    pid_t   pid;
    char    *path;

    while (cmds)
    {
        if (cmds->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();
        if (pid == 0)  
        {

            if (cmds->heredoc)
            {
                int tmp_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (tmp_fd == -1)
                {
                    perror("minishell: heredoc temp file");
                    exit(1);
                }

                char *line;
                while (1)
                {
                    line = readline("> ");
                    if (!line || ft_strncmp(line, cmds->heredoc, 5) == 0)
                        break;
                    write(tmp_fd, line, ft_strlen(line));
                    write(tmp_fd, "\n", 1);
                    free(line);
                }
                free(line);
                close(tmp_fd);

                tmp_fd = open(".heredoc_tmp", O_RDONLY);
                if (tmp_fd == -1)
                {
                    perror("minishell: heredoc read");
                    exit(1);
                }
                dup2(tmp_fd, STDIN_FILENO);
                close(tmp_fd);
            }

            // input redirect
            if (cmds->redir_in)
            {
                int fd = open(cmds->redir_in, O_RDONLY);
                if (fd == -1)
                {
                    perror("infile");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            else if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // output redirect
            if (cmds->redir_append)
            {
                int fd = open(cmds->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror("append");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else if (cmds->redir_out)
            {
                int fd = open(cmds->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("outfile");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else if (cmds->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            // close child pipe
            if (pipefd[0])
                close(pipefd[0]);

            // builtins
            if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
                exit(build_exit(cmds->args));
            else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
                exit(command_export(env, cmds->args));
            else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
                exit(command_unset(env, cmds->args));
            else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
                exit(builtin_env(*env));

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
        else if (pid > 0)  // Parent process
        {
            if (prev_fd != -1)
                close(prev_fd);
            if (cmds->next)
            {
                close(pipefd[1]);
                prev_fd = pipefd[0];
            }
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork");
            exit(1);
        }

		cmds = cmds->next;
	}
}

