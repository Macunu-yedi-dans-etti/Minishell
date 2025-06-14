/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:53:28 by musoysal         ###   ########.fr       */
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
		ft_putstr_fd("minishell: history file could not be opened\n", 2);
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
		ft_double_free(&p->envp);//perror( NULL, 1); fork fail fork hatası tespit
		exit(1);
	}
	if (!pid)
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

	str = getcwd(NULL, 0);//PWD
	if (str)
	{
		prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
		free(str);
	}
	shlvl = mini_getenv("SHLVL", prompt.envp, 5);//SHLVL
	if (!shlvl || ft_atoi(shlvl) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(shlvl) + 1);
	free(shlvl);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
 	str = mini_getenv("PATH", prompt.envp, 4);//PATH
	if (!str)
		prompt.envp = mini_setenv("PATH", \
			"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", \
			prompt.envp, 4);
	free(str);
	str = mini_getenv("_", prompt.envp, 1);//  _ değişkeni (program adı argv[0])
	if (!str && av[0])
		prompt.envp = mini_setenv("_", av[0], prompt.envp, 1);
	free(str);

	return (prompt);
}

static t_req	responses(char **av, char **env)
{
	t_req	response;

	response.cmds = NULL;
	response.envp = ft_double_copy(env);
	response.exit_stat = 0;
	g_exit_status = 0;
	tier_pid(&response);
	response = init_variable(response, NULL, av);
	return (response);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*output;
	char	**tokens;
	t_list	*cmds;
	t_list	*tmp;
	t_req	response;

	(void)ac;
	response = responses(av, env);
	if (read_history_file(".minishell_history") == 0)
		read_history(".minishell_history");
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = mini_getinput(response);
		output = readline(input ? input : "guest@minishell $ ");
		free(input);
		if (output && output[0])
		{
			add_history(output);
			tokens = tokenize_input(output);
			cmds = parse_tokens(tokens, &response);
			tmp = cmds;
			while (tmp)
			{
				t_shell *cmd = tmp->content;
				if (cmd->full_cmd && cmd->full_cmd[0])
					cmd->full_path = resolve_path(cmd->full_cmd[0], response.envp);
				tmp = tmp->next;
			}
			execute_cmds(cmds, &response);
			free_cmds(cmds);
			ft_double_free(&tokens);
		}
		if (!output)
		{
			write(1, "exit\n", 5);
			break ;
		}
		free(output);
	}
	free_all(&response);
	exit(response.exit_stat);
}
