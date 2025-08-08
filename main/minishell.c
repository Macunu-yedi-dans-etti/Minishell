/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/09 00:33:01 by haloztur         ###   ########.fr       */
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
	res->tokens = NULL;
	output = get_input_prompt(res);
	if (!output)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		rl_clear_history();
		if (res->tokens)
		{
			free_string_array(res->tokens);
			res->tokens = NULL;
			free_all(res);//2
		}
		return (0);
	}
	if (output[0])
	{
		tokens = process_input(output, res);
		if (tokens)
		{
			res->tokens = tokens;
			execute_pipeline(tokens, res);
			free_string_array(tokens);
			tokens = NULL;
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
		if (res->tokens)
		{
			free_string_array(res->tokens);
			res->tokens = NULL;
		}
		res->heredoc_interrupted = 0;
	}
	free(output);
	if (res->should_exit)
	{	
		if (res->tokens)
		{
			free_string_array(res->tokens);
			res->tokens = NULL;
		}
		return (0);
	}
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
		free_all(&res);
		return (1);
	}
	while (process_main_loop(&res))
		;
	rl_clear_history();
	free_all(&res);
	return (res.exit_stat);
}
