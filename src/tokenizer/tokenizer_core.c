/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:40:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/28 21:26:50 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token*get_operator_token(const char *input, int *i)
{
	char	op[3];

	if ((input[*i] == '<' || input[*i] == '>') && input[*i] == input[*i + 1])
	{
		op[0] = input[*i];
		op[1] = input[*i];
		op[2] = '\0';
		*i += 2;
	}
	else
	{
		op[0] = input[*i];
		op[1] = '\0';
		(*i)++;
	}
	return (create_token(op, QUOTE_NONE));
}

t_token	*get_word_token(const char *input, int *i)
{
	char quote_char = input[*i];
	if (input[*i] == '\'' || input[*i] == '"')
	{
		int start = ++(*i);
		while (input[*i] && input[*i] != quote_char)
			(*i)++;
		if (!input[*i]) // Kapanmayan tırnak
			return NULL;
		int len = *i - start;
		char *str = ft_substr(input, start, len);
		(*i)++; // Kapanan tırnağı atla
		return create_token(str,
					quote_char == '\'' ? QUOTE_SINGLE : QUOTE_DOUBLE);
	}
	else
	{
		int start = *i;
		while (input[*i] && !is_separator(input[*i]) &&
		   !is_operator(input[*i]) && input[*i] != '\'' && input[*i] != '"')
			(*i)++;
	int len = *i - start;
	char *str = ft_substr(input, start, len);
	return create_token(str, QUOTE_NONE);
	}
}
