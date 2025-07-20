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

t_token	**tokenize_and_validate(char *trimmed_output, t_req *res)
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
	if (!check_valid_tokens(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
