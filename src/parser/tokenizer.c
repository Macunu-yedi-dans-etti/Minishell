/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:20 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 10:57:51 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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
	char *result;
	int len = 0;
	int capacity = 32;

	result = malloc(capacity);
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
				int substr_len = j - *i - 1;
				if (len + substr_len >= capacity - 1)
				{
					while (len + substr_len >= capacity - 1)
						capacity *= 2;
					char *new_result = realloc(result, capacity);
					if (!new_result)
					{
						free(substr);
						free(result);
						return NULL;
					}
					result = new_result;
				}
				memcpy(result + len, substr, substr_len);
				len += substr_len;
				result[len] = '\0';
				free(substr);
				*i = j + 1;
			}
			else
			{
				if (len >= capacity - 1)
				{
					capacity *= 2;
					char *new_result = realloc(result, capacity);
					if (!new_result)
					{
						free(result);
						return NULL;
					}
					result = new_result;
				}
				result[len++] = input[(*i)++];
				result[len] = '\0';
			}
		}
		else
		{
			if (len >= capacity - 1)
			{
				capacity *= 2;
				char *new_result = realloc(result, capacity);
				if (!new_result)
				{
					free(result);
					return NULL;
				}
				result = new_result;
			}
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
	int capacity;

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
		if (token && token->str && token->str[0] != '\0')
		{
			if (count >= capacity - 1)
			{
				capacity *= 2;
				tmp = malloc(sizeof(t_token *) * capacity);
				if (!tmp)
				{
					free_tokens(tokens);
					return (NULL);
				}
				j = -1;
				while (++j < count)
					tmp[j] = tokens[j];
				free(tokens);
				tokens = tmp;
			}
			tokens[count++] = token;
			tokens[count] = NULL;
		}
		else if (token)
		{
			free(token->str);
			free(token);
		}
	}
	return (tokens);
}
