/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:20 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/24 19:47:00 by musoysal         ###   ########.fr       */
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
	token->quote = quote;
	return (token);
}

static t_token	*get_token(const char *input, int *i)
{
	int		start;
	char	quote;
	char	op;
	t_token	*token;
	int		len;
	char	op_str[3];
	char	*substr;

	while (input[*i] && is_separator(input[*i]))
		(*i)++;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		len = *i - start;
		if (input[*i] == quote)
			(*i)++;
		substr = ft_substr(input, start, len);
		token = create_token(substr, (quote == '\'') ? 1 : 2);
		free(substr);
		return (token);
	}
	else if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		op = input[*i];
		(*i) += 2;
		if (op == '>')
			token = create_token(">>", 0);
		else
			token = create_token("<<", 0);
		return (token);
	}
	else if (is_operator(input[*i]))
	{
		op_str[0] = input[*i];
		op_str[1] = 0;
		(*i)++;
		token = create_token(op_str, 0);
		return (token);
	}
	else
	{
		start = *i;
		while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
			(*i)++;
		substr = ft_substr(input, start, *i - start);
		token = create_token(substr, 0);
		free(substr);
		return (token);
	}
}

t_token	**tokenize_input(const char *input)
{
	t_token	**tokens;
	t_token	*token;
	t_token	**tmp;
	int		i;
	int		count;
	int		j;

	i = 0;
	count = 0;
	tokens = NULL;
	while (input[i])
	{
		token = get_token(input, &i);
		if (token && token->str && token->str[0] != '\0')
		{
			tmp = malloc(sizeof(t_token *) * (count + 2));
			j = 0;
			while (j < count)
			{
				tmp[j] = tokens[j];
				j++;
			}
			tmp[count] = token;
			tmp[count + 1] = NULL;
			free(tokens);
			tokens = tmp;
			count++;
		}
		else if (token)
		{
			free(token->str);
			free(token);
		}
	}
	return (tokens);
}
