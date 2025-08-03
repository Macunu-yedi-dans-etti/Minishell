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

char	*get_operator_string(const char *input, int *i)
{
	char	op[3];

	if ((input[*i] == '<' || input[*i] == '>') && input[*i] == input[*i + 1]) // heredoc veya append redirection
	{
		op[0] = input[*i];
		op[1] = input[*i];
		op[2] = '\0';
		*i += 2;
	}
	else // normal redirection veya pipe
	{
		op[0] = input[*i];
		op[1] = '\0';
		(*i)++;
	}
	return (ft_strdup(op));
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
	if (!append_char_to_result(result, &state->len, &state->capacity, quote_char))
		return (0);
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
	{
		if (!append_char_to_result(result, &state->len, &state->capacity,
				input[*i]))
			return (0);
		(*i)++;
	}
	if (input[*i] == quote_char)
	{
		if (!append_char_to_result(result, &state->len, &state->capacity, quote_char))
			return (0);
		(*i)++;
	}
	return (1);
}

char	*get_word_string(const char *input, int *i)
{
	char			*result;
	t_token_state	state;

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
			if (!handle_quoted_section(input, i, &result, &state))
				return (free(result), NULL);
		}
		else
		{
			if (!append_char_to_result(&result, &state.len, &state.capacity,
					input[*i]))
				return (free(result), NULL);
			(*i)++;
		}
	}
	return (result);
}
/*
input(prompt) :echo "$USER"'$USER'
ilk işlem tokenize
tokens[0] =  echo
tokens[1] = ""$USER"'$USER'"
tokens[2] = NULL

quote kontrol
tokens[0] =  echo için tırnak yoksa ve $ yoksa diğerine geç
tokens[1] = "$USER"'$USER'" için tırnak var ve $ var ozaman işleme geç fakat önce qoate türü doğru kullanılmşmı kontrol et
tokens[1] = "$USER"'$USER'" için tırnak türü doğru kullanılmışsa ve $ var ise expanda et doğru değilse fail quote
tokens[1] = "haloztur$USER" doğru olduğu için bu şekilde olucak 
tokens[2] = NULL

daha sonra tokenleri tek tek redirin redir out veya heredoc olup olmadığını veya pipe olup olmadığını denetleyecek
bir fonksiyon yazılacak

daha sonra execute_pipeline fonksiyonuna gönderilecek

*/