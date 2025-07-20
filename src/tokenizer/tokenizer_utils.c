/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:40:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 14:40:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*create_token(const char *str, int quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->quote = quote;
	return (token);
}

t_token	*create_token_and_free(char *str, int quote)
{
	t_token	*token;

	token = create_token(str, quote);
	free(str);
	return (token);
}
