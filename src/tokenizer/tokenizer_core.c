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

	if ((input[*i] == '<' || input[*i] == '>')
		&& input[*i] == input[*i + 1])
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
	return (ft_strdup(op));
}

static int	handle_quoted_section(const char *input, int *i,
		t_word_builder *builder)
{
	char	quote_char;

	quote_char = input[*i];
	if (!append_char_to_result(builder->result, builder->len,
			builder->capacity, quote_char))
		return (0);
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
	{
		if (!append_char_to_result(builder->result, builder->len,
				builder->capacity, input[*i]))
			return (0);
		(*i)++;
	}
	if (input[*i] == quote_char)
	{
		if (!append_char_to_result(builder->result, builder->len,
				builder->capacity, quote_char))
			return (0);
		(*i)++;
	}
	return (1);
}

static int	process_character(const char *input, int *i,
	t_word_builder *builder)
{
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (!handle_quoted_section(input, i, builder))
			return (0);
	}
	else
	{
		if (!append_char_to_result(builder->result, builder->len,
				builder->capacity, input[*i]))
			return (0);
		(*i)++;
	}
	return (1);
}

char	*get_word_string(const char *input, int *i)
{
	char			*result;
	int				len;
	int				capacity;
	t_word_builder	builder;

	builder = init_word_builder(&result, &len, &capacity);
	if (!result)
		return (NULL);
	while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
	{
		if (!process_character(input, i, &builder))
			return (free(result), NULL);
	}
	return (result);
}
