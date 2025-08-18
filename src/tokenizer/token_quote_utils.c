/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:09:32 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 09:00:59 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	validate_quotes(char *str, int i, int single_count,
	int double_count)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			single_count++;
			in_single = !in_single;
		}
		else if (str[i] == '"' && !in_single)
		{
			double_count++;
			in_double = !in_double;
		}
		i++;
	}
	return ((single_count % 2 == 0 && double_count % 2 == 0));
}

/* handle_single_quotes moved to token_quote_utils2.c */

static char	*append_char(char *result, char c)
{
	char	tmp[2];
	char	*new_res;

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(result, tmp);
	free(result);
	return (new_res);
}

static char	*handle_double_quotes(char *input, int *i, char *result, t_req *res)
{
	char	*temp;
	char	*expanded;

	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			temp = expand_token_var(input, i, res);
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = expanded;
		}
		else
			result = append_char(result, input[(*i)++]);
	}
	if (input[*i] == '"')
		(*i)++;
	return (result);
}

static char	*handle_no_quotes(char *input, int *i, char *result, t_req *res)
{
	char	c[2];
	char	*temp;
	char	*expanded;

	if (input[*i] == '$')
	{
		temp = expand_token_var(input, i, res);
		expanded = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = expanded;
	}
	else
	{
		c[0] = input[(*i)++];
		c[1] = '\0';
		temp = ft_strjoin(result, c);
		free(result);
		result = temp;
	}
	return (result);
}

char	*process_quotes_and_expand(char *input, t_req *res)
{
	char	*result;
	int		i;

	if (!input)
		return (ft_strdup(""));
	if (!validate_quotes(input, 0, 0, 0))
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			result = handle_single_quotes(input, &i, result);
		else if (input[i] == '"')
			result = handle_double_quotes(input, &i, result, res);
		else
			result = handle_no_quotes(input, &i, result, res);
	}
	return (result);
}
