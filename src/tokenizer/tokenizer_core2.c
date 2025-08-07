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

static char	*gechar_string(const char *input, int *i)
{
	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (is_operator(input[*i]))
		return (get_operator_string(input, i));
	return (get_word_string(input, i));
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



char	**tokenize_input(const char *input)
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
	while (input[i])
	{
		token_str = gechar_string(input, &i);
		if (!token_str)
		{
			// Cleanup on tokenization failure
			free_string_array(tokens);
			return (NULL);
		}
		if (!add_string_to_array(&tokens, token_str, &count, &capacity))
		{
			// Cleanup on array expansion failure
			free_string_array(tokens);
			return (NULL);
		}
	}
	return (tokens);
}

int	resize_string_array(char ***tokens, int *capacity, int count)
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
