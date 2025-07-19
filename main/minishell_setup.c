/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_req	init_variable_continue(t_req prompt, char **av);

static void	tier_pid(t_req *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_double_free(&p->envp);
		ms_error(ERR_FORK, NULL, 1, NULL);
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
	return (init_variable_continue(prompt, av));
}

static t_req	init_variable_continue(t_req prompt, char **av)
{
	char	*str;

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

t_req	setup(char **av, char **env)
{
	t_req	res;

	res.cmds = NULL;
	res.envp = ft_double_copy(env);
	res.exit_stat = 0;
	res.exit_stat = 0;
	tier_pid(&res);
	res = init_variable(res, NULL, av);
	return (res);
}
