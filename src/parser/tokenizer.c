/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:20 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/12 03:20:02 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token	*create_token(const char *str, int quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	if (!token->str)
		return (free(token), NULL);
	token->quote = quote;
	return (token);
}

static t_token	*get_quoted_token(const char *input, int *i)
{
	t_token	*token;
	char	*substr;
	char	quote;
	int		start;
	int		quote_type;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (ms_error(ERR_QUOTE, NULL, 2), NULL);
	substr = ft_substr(input, start, *i - start);
	(*i)++;
	if (!substr)
		return (NULL);
	if (quote == '\'')
		quote_type = 1;
	else
		quote_type = 2;
	token = create_token(substr, quote_type);
	free(substr);
	return (token);
}

static t_token	*get_operator_token(const char *input, int *i)
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
	return (create_token(op, 0));
}

static t_token	*get_word_token(const char *input, int *i)
{
	t_token	*token;
	char	*substr;
	int		start;

	start = *i;
	while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
		(*i)++;
	substr = ft_substr(input, start, *i - start);
	if (!substr)
		return (NULL);
	token = create_token(substr, 0);
	free(substr);
	return (token);
}

static t_token	*get_token(const char *input, int *i)
{
	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '\'' || input[*i] == '"')
		return (get_quoted_token(input, i));
	if (is_operator(input[*i]))
		return (get_operator_token(input, i));
	return (get_word_token(input, i));
}

t_token	**tokenize_input(const char *input)
{
	t_token	**tokens;
	t_token	*token;
	t_token	**tmp;
	int		i;
	int		j;
	int		count;

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
