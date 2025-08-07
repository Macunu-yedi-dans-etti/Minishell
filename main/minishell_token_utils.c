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

static int	has_quotes_or_variables(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	**quote_control_and_expand(char **tokens, t_req *res)
{
	int i;
	char *expanded;
	
	i = 0;
	while (tokens[i])
	{
		// Quote kontrolü ve expansion
		if (has_quotes_or_variables(tokens[i]))
		{
			expanded = process_quotes_and_expand(tokens[i], res);
			if (!expanded)
			{
				// Quote error - ms_error kullanarak standardize edilmiş hata
				ms_error(ERR_QUOTE, NULL, 258, res);
				return (free_string_array(tokens), NULL);
			}
			free(tokens[i]);
			tokens[i] = expanded;
		}
		i++;
	}
	return (tokens);
}

char	**tokenize_and_validate(char *trimmed_output, t_req *res)
{
	char **tokens;
	
	// 1. İlk tokenization - sadece ayır
	tokens = tokenize_input(trimmed_output);
	if (!tokens)
		return (NULL);
	
	// 2. Quote control ve expansion
	tokens = quote_control_and_expand(tokens, res);
	if (!tokens)
	{
		// Cleanup on error
		return (NULL);
	}
	// 3. res'e token'ları kaydet
	res->tokens = tokens;
	
	return (tokens);
}