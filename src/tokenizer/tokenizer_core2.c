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

static int	process_token(t_token ***tokens, t_token *token, int *count,
		int *capacity);

static t_token	*get_token(const char *input, int *i)
{
	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (is_operator(input[*i]))
		return (get_operator_token(input, i));
	return (get_word_token(input, i));
}

static int	add_token_to_array(t_token ***tokens, t_token *token, int *count,
		int *capacity)
{
	if (*count >= *capacity - 1 && !resize_token_array(tokens, capacity,
			*count))
		return (0);
	(*tokens)[(*count)++] = token;
	(*tokens)[*count] = NULL;
	return (1);
}

t_token	**tokenize_input(const char *input)
{
	t_token	**tokens;
	t_token	*token;
	int		i;
	int		count;
	int		capacity;

	i = 0;
	count = 0;
	capacity = 16;
	tokens = malloc(sizeof(t_token *) * capacity);
	if (!tokens)
		return (NULL);
	tokens[0] = NULL;
	while (input[i])
	{
		token = get_token(input, &i);
		if (!token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		if (!process_token(&tokens, token, &count, &capacity))
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}

static int	process_token(t_token ***tokens, t_token *token, int *count,
		int *capacity)
{
	if (token && token->str && (token->str[0] != '\0'
			|| token->quote != QUOTE_NONE))
	{
		if (!add_token_to_array(tokens, token, count, capacity))
			return (0);
	}
	else if (token)
	{
		free(token->str);
		free(token);
	}
	return (1);
}

int	resize_token_array(t_token ***tokens, int *capacity, int count)
{
	t_token	**tmp;
	int		j;

	*capacity *= 2;
	tmp = malloc(sizeof(t_token *) * (*capacity));
	if (!tmp)
		return (0);
	j = -1;
	while (++j < count)
		tmp[j] = (*tokens)[j];
	free(*tokens);
	*tokens = tmp;
	return (1);
}
