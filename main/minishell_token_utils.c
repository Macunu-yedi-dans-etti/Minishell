/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:00:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 10:00:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	**tokenize_and_validate(char *trimmed_output, t_req *res) // temizlenmiş input aslında ve yanına ek structını yolluyor içinde envsi vs. var
{
	char		*expanded_input;
	t_token		**tokens;

	if (needs_retokenization(trimmed_output))
	{
		expanded_input = expand_str(trimmed_output, res->envp, QUOTE_NONE, res);
		free(trimmed_output);
		tokens = tokenize_input(expanded_input);
		free(expanded_input);
	}
	else
	{
		tokens = tokenize_input(trimmed_output);
		free(trimmed_output);
		if (tokens)
			tokens = expand_tokens(tokens, res);
	}
	if (!tokens)
		return (NULL);
	if (!check_valid_tokens(tokens)) // Geçerli token yoksa boş array döner
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

/*
tokenize input

Step-by-step tokenization:

i=0: "ls -la | grep txt"
     ^^
get_token() → token = {str: "ls", quote: QUOTE_NONE}
process_token() → tokens[0] = "ls", count = 1

i=3: "ls -la | grep txt"
        ^^^
get_token() → token = {str: "-la", quote: QUOTE_NONE}  
process_token() → tokens[1] = "-la", count = 2

i=7: "ls -la | grep txt"
           ^
get_token() → token = {str: "|", quote: QUOTE_NONE}
process_token() → tokens[2] = "|", count = 3

i=9: "ls -la | grep txt"
             ^^^^
get_token() → token = {str: "grep", quote: QUOTE_NONE}
process_token() → tokens[3] = "grep", count = 4

i=14: "ls -la | grep txt"
                   ^^^
get_token() → token = {str: "txt", quote: QUOTE_NONE}
process_token() → tokens[4] = "txt", count = 5

Final: ["ls", "-la", "|", "grep", "txt", NULL]
*/