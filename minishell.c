/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 06:55:12 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	read_history_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ms_error(ERR_NO_DIR, "history file could not be opened", 1);
		return (-1);
	}
	close(fd);
	return (0);
}

static void	tier_pid(t_req *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_double_free(&p->envp);
		ms_error(ERR_FORK, NULL, 1);
		exit(1);
	}
	if (pid == 0)
	{
		ft_double_free(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_req	init_variable(t_req prompt, char *str, char **av)
{
	char	*num;
	char	*shlvl;

	str = getcwd(NULL, 0);
	if (str)
	{
		prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
		free(str);
	}
	shlvl = mini_getenv("SHLVL", prompt.envp, 5);
	if (!shlvl || ft_atoi(shlvl) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(shlvl) + 1);
	free(shlvl);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin",
				prompt.envp, 4);
	free(str);
	str = mini_getenv("_", prompt.envp, 1);
	if (!str && av[0])
		prompt.envp = mini_setenv("_", av[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_req	setup(char **av, char **env)
{
	t_req	res;

	res.cmds = NULL;
	res.envp = ft_double_copy(env);
	res.exit_stat = 0;
	g_exit_status = 0;
	tier_pid(&res);
	res = init_variable(res, NULL, av);
	return (res);
}

static void	append_history_file(const char *filename, const char *line)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ms_error(ERR_NO_DIR, "history file could not be opened for append", 1);
		return ;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*output;
	char	*old;
	int		i;
	t_token	**tokens;
	t_list	*cmds;
	t_list	*tmp;
	t_req	res;
	t_shell	*cmd;

	(void)ac;
	res = setup(av, env);
	if (read_history_file(".minishell_history") == 0)
		read_history(".minishell_history");
	while (1)
	{
		setup_signals();
		input = mini_getinput(res);
		output = readline(input ? input : "guest@minishell $ ");
		free(input);
		if (!output)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (output[0])
		{
			add_history(output);
			append_history_file(".minishell_history", output);
			tokens = tokenize_input(output);
			i = 0;
			while (tokens && tokens[i])
			{
				old = tokens[i]->str;
				tokens[i]->str = expand_str(old, res.envp, tokens[i]->quote);
				free(old);
				i++;
			}
			cmds = parse_tokens(tokens, &res);
			tmp = cmds;
			while (tmp)
			{
				cmd = tmp->content;
				if (cmd->full_cmd && cmd->full_cmd[0])
					cmd->full_path = resolve_path(cmd->full_cmd[0], res.envp);
				tmp = tmp->next;
			}
			res.exit_stat = g_exit_status;
			execute_cmds(cmds, &res);
			free_cmds(cmds);
			free_tokens(tokens);
		}
		free(output);
	}
	free_all(&res);
	exit(g_exit_status);
}

