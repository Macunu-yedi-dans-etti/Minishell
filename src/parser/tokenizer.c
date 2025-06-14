/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:20 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:45:01 by musoysal         ###   ########.fr       */
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

static char	*get_token(const char *input, int *i)
{
	int		start;
	char	quote;
	char	op;

	while (is_separator(input[*i]))
		(*i)++;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
		return (ft_substr(input, start + 1, *i - start - 2));
	}
	else if ((input[*i] == '>' || input[*i] == '<')
		&& input[*i + 1] == input[*i])
	{
		op = input[*i];
		(*i) += 2;
		if (op == '>')
			return (ft_strdup(">>"));
		else
			return (ft_strdup("<<"));
	}
	else if (is_operator(input[*i]))
		return (ft_substr(input, (*i)++, 1));
	else
	{
		while (input[*i] && !is_separator(input[*i]) && !is_operator(input[*i]))
			(*i)++;
		return (ft_substr(input, start, *i - start));
	}
}

char	**tokenize_input(const char *input)
{
	char	**tokens;
	char	*token;
	int		i;
	int		count;

	tokens = NULL;
	i = 0;
	count = 0;
	while (input[i])
	{
		token = get_token(input, &i);
		if (token && token[0] != '\0')
		{
			tokens = ft_double_extension(tokens, token);
			free(token);
			count++;
		}
		else
			free(token);
	}
	return (tokens);
}
