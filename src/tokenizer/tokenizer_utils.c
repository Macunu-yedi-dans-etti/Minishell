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
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*reallocate_result(char *result, int *capacity)
{
	char	*new_result;
	int		new_capacity;

	new_capacity = (*capacity) * 2;
	new_result = malloc(new_capacity);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(new_result, result, *capacity);
	free(result);
	*capacity = new_capacity;
	return (new_result);
}

int	append_char_to_result(char **result, int *len, int *capacity, char c)
{
	if (*len >= *capacity - 1)
	{
		*result = reallocate_result(*result, capacity);
		if (!*result)
			return (0);
	}
	(*result)[*len] = c;
	(*len)++;
	(*result)[*len] = '\0';
	return (1);
}

