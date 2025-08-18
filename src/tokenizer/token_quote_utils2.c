/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:12:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/18 09:01:02 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_single_quotes(char *input, int *i, char *result)
{
	int		start;
	char	*temp;
	char	*expanded;

	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i])
	{
		temp = ft_substr(input, start, *i - start);
		expanded = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = expanded;
		(*i)++;
	}
	return (result);
}
