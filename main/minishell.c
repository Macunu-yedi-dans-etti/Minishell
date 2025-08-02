/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:49:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/02 22:25:42 by haloztur         ###   ########.fr       */
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
	t_token		**tokens;

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
			execute_pipeline(tokens, res); // execute_pipeline(tokens, res); burası
			free_tokens(tokens);
		}
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
	while (process_main_loop(&res))
		;
	rl_clear_history();
	free_all(&res);
	return (res.exit_stat);
}
