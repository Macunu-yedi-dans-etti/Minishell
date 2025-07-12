/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:20 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/12 23:43:55 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

static int is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

static int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token *create_token(const char *str, int quote)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	if (!token->str)
		return (free(token), NULL);
	token->quote = quote;
	return (token);
}

static t_token *get_operator_token(const char *input, int *i)
{
	char op[3];

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
	return (create_token(op, 0));
}

static t_token *get_word_token(const char *input, int *i)
{
	int quote_type = 0;
	char *result = malloc(1);
	int len = 0;
	if (!result)
		return NULL;
	result[0] = '\0';
	while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			char q = input[*i];
			int qtype = (q == '\'') ? 1 : 2;
			if (qtype == 1)
				quote_type = 1;
			if (qtype == 2 && quote_type == 0)
				quote_type = 2;
			int j = *i + 1;
			while (input[j] && input[j] != q)
				j++;
			if (input[j] == q)
			{
				char *substr = ft_substr(input, *i + 1, j - *i - 1);
				if (!substr)
				{
					free(result);
					return NULL;
				}
				int oldlen = len;
				len += j - *i - 1;
				result = realloc(result, len + 1);
				if (!result)
				{
					free(substr);
					return NULL;
				}
				memcpy(result + oldlen, substr, j - *i - 1);
				result[len] = '\0';
				free(substr);
				*i = j + 1;
			}
			else
			{
				// unmatched quote, treat as literal
				result = realloc(result, len + 2);
				result[len++] = input[(*i)++];
				result[len] = '\0';
			}
		}
		else
		{
			result = realloc(result, len + 2);
			result[len++] = input[(*i)++];
			result[len] = '\0';
		}
	}
	t_token *token = create_token(result, quote_type);
	free(result);
	return token;
}

static t_token *get_token(const char *input, int *i)
{
	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (is_operator(input[*i]))
		return (get_operator_token(input, i));
	return (get_word_token(input, i));
}

t_token **tokenize_input(const char *input)
{
	t_token **tokens;
	t_token *token;
	t_token **tmp;
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	tokens = NULL;
	while (input[i])
	{
		token = get_token(input, &i);
		if (!token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		if (token && token->str && token->str[0] != '\0')
		{
			tmp = malloc(sizeof(t_token *) * (count + 2));
			if (!tmp)
				return (free_tokens(tokens), NULL);
			j = -1;
			while (++j < count)
				tmp[j] = tokens[j];
			tmp[count++] = token;
			tmp[count] = NULL;
			free(tokens);
			tokens = tmp;
		}
		else if (token)
		{
			free(token->str);
			free(token);
		}
	}
	return (tokens);
}
