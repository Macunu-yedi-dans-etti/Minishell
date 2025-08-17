/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:19:52 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:19:52 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_operator_string(const char *input, int *i)
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

static char	*get_char_string(const char *input, int *i)
{
	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (is_operator(input[*i]))
		return (get_operator_string(input, i));
	return (get_word_string(input, i));
}

static int	resize_string_array(char ***tokens, int *capacity, int count)
{
	char	**tmp;
	int		j;

	*capacity *= 2;
	tmp = malloc(sizeof(char *) * (*capacity));
	if (!tmp)
		return (0);
	j = -1;
	while (++j < count)
		tmp[j] = (*tokens)[j];
	free(*tokens);
	*tokens = tmp;
	return (1);
}

static int	add_string_to_array(char ***tokens, char *token_str, int *count,
		int *capacity)
{
	if (*count >= *capacity - 1 && !resize_string_array(tokens, capacity,
			*count))
		return (0);
	(*tokens)[(*count)++] = token_str;
	(*tokens)[*count] = NULL;
	return (1);
}

char	**tokenize_input(const char *trimmed_input)
{
	char	**tokens;
	char	*token_str;
	int		i;
	int		count;
	int		capacity;

	i = 0;
	count = 0;
	capacity = 16;
	tokens = malloc(sizeof(char *) * capacity);
	if (!tokens)
		return (NULL);
	tokens[0] = NULL;
	while (trimmed_input[i])
	{
		token_str = get_char_string(trimmed_input, &i);
		if (!token_str)
		{
			ft_double_free(&tokens);
			return (NULL);
		}
		if (!add_string_to_array(&tokens, token_str, &count, &capacity))
		{
			free(token_str);
			ft_double_free(&tokens);
			return (NULL);
		}
	}
	return (tokens);
}
