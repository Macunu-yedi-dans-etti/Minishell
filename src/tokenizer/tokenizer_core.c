/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:40:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 14:40:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*get_operator_token(const char *input, int *i)
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

static char	*reallocate_result(char *result, int *capacity)
{
	char	*new_result;
	int		new_capacity;

	new_capacity = (*capacity) * 2;
	new_result = malloc(new_capacity);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(new_result, result, *capacity);
	free(result);
	*capacity = new_capacity;
	return (new_result);
}

static int	append_char_to_result(char **result, int *len, int *capacity,
		char c)
{
	if (*len >= *capacity - 1)
	{
		*result = reallocate_result(*result, capacity);
		if (!*result)
			return (0);
	}
	(*result)[*len] = c;
	(*len)++;
	(*result)[*len] = '\0';
	return (1);
}

static int	handle_quoted_section(const char *input, int *i, char **result,
		t_token_state *state)
{
	char	quote_char;

	quote_char = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
	{
		if (!append_char_to_result(result, &state->len, &state->capacity,
				input[*i]))
			return (0);
		(*i)++;
	}
	if (input[*i] == quote_char)
		(*i)++;
	return (1);
}

t_token	*get_word_token(const char *input, int *i)
{
	int				has_single;
	int				has_double;
	int				has_unquoted;
	char			*result;
	t_token_state	state;

	has_single = 0;
	has_double = 0;
	has_unquoted = 0;
	state.len = 0;
	state.capacity = 32;
	result = malloc(state.capacity);
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (input[*i] == '\'')
				has_single = 1;
			else
				has_double = 1;
			if (!handle_quoted_section(input, i, &result, &state))
				return (free(result), NULL);
		}
		else
		{
			has_unquoted = 1;
			if (!append_char_to_result(&result, &state.len, &state.capacity,
					input[*i]))
				return (free(result), NULL);
			(*i)++;
		}
	}
	return (create_token_and_free(result, determine_quote_type(has_single, has_double,
				has_unquoted)));
}
