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

char	**quote_control_and_expand(t_req *res)
{
	int		i;
	char	*expanded;
	
	i = 0;
	while (res->tokens[i])
	{
		if (has_quotes_or_variables(res->tokens[i]))
		{
			expanded = process_quotes_and_expand(res->tokens[i], res);
			if (!expanded)
			{
				ms_error(ERR_QUOTE, NULL, 258, res);
				return (free_string_array(res->tokens), res->tokens = NULL, NULL);
			}
			free(res->tokens[i]);
			res->tokens[i] = expanded;
		}
		i++;
	}
	return (res->tokens);
}

int	tokenize_and_validate(t_req *res)
{
	res->tokens = tokenize_input(res->trimmed_input);
	if (!res->tokens)
		return (0);
	res->tokens = quote_control_and_expand(res);
	if (!res->tokens)
		return (0);
	return (1);
}