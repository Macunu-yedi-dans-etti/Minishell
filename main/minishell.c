/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/15 14:37:21 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_input_prompt(t_req *res)
{
	char	*input;
	char	*output;

	input = mini_getinput(*res);
	if (input)
		output = readline(input);
	else
		output = readline("guest@minishell $ ");
	free(input);
	return (output);
}

static int	process_main_loop(t_req *res)
{
	char		*output;

	setup_signals(res);
	ft_double_free(&res->tokens);
	output = get_input_prompt(res);
	if (!output)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		return (rl_clear_history(), free_req(res), 0);
	}
	if (output[0])
	{
		if (process_input(output, res))
		{
			execute_pipeline(res);
			ft_double_free(&res->tokens);
		}
	}
	if (res->heredoc_interrupted)
	{
		if (res->cmds)
		{
			free_cmds(res->cmds);
			res->cmds = NULL;
		}
		if (res->tokens)
			ft_double_free(&res->tokens);
		res->heredoc_interrupted = 0;
	}
	free(output);
	if (res->should_exit)
	{
		if (res->tokens)
			ft_double_free(&res->tokens);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_req	res;

	if (ac != 1)
	{
		ft_putstr_fd("Usage: ", 2);
		if (av && av[0])
			ft_putstr_fd(av[0], 2);
		return (1);
	}
	res = setup(av, env);
	if (!res.envp)
	{
		ft_putstr_fd("Error: Environment setup failed.\n", 2);
		free_req(&res);
		return (1);
	}
	while (process_main_loop(&res))
		;
	rl_clear_history();
	free_req(&res);
	return (res.exit_stat);
}
