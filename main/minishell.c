/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/07 19:13:33 by musoysal         ###   ########.fr       */
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
	char		**tokens;

	setup_signals();
	output = get_input_prompt(res);
	if (!output)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		rl_clear_history();
		return (0);
	}
	if (output[0])
	{
		tokens = process_input(output, res);
		if (tokens)
		{
			execute_pipeline(tokens, res);
			free_string_array(tokens);
			res->tokens = NULL;
		}
	}
	// Interrupt sonrası cleanup
	if (res->heredoc_interrupted)
	{
		if (res->cmds)
		{
			free_cmds(res->cmds);
			res->cmds = NULL;
		}
		res->heredoc_interrupted = 0;
	}
	// Cleanup any remaining tokens if interrupted
	if (res->tokens)
	{
		free_string_array(res->tokens);
		res->tokens = NULL;
	}
	// Additional cleanup for any remaining commands
	if (res->cmds)
	{
		free_cmds(res->cmds);
		res->cmds = NULL;
	}
	// Check if we were interrupted and need to exit
	if (res->exit_stat == 130) // SIGINT exit code
	{
		free(output);
		return (0);
	}
	free(output);
	if (res->should_exit)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_req	res;

	if (ac != 1)
	{
		fprintf(stderr, "Usage: %s\n", av[0]);
		return (1);
	}
	res = setup(av, env); // setup fonksiyonu env ve diğer değişkenleri ayarlar
	if (!res.envp)
	{
		fprintf(stderr, "Error: Environment setup failed.\n");
		return (1);
	}
	set_signal_req(&res); // Set signal handler to access res for cleanup
	while (process_main_loop(&res))
		;
	rl_clear_history();
	free_all(&res);
	return (res.exit_stat);
}
