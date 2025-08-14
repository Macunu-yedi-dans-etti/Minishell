/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/14 18:50:51 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_token_var(char *str, int *i, t_req *res)
{
	int		start;
	char	*name;
	char	*value;

	start = ++(*i);
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(res->exit_stat));
	if (str[*i] == '_')
		return ((*i)++, ft_strdup("minishell"));
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	name = ft_substr(str, start, *i - start);
	value = mini_getenv(name, res->envp, 1);
	free(name);
	if (value)
		return (value);
	else
		return (ft_strdup(""));
}

int	validate_quotes(char *str)
{
	int		i;
	int		single_count;
	int		double_count;
	int		in_single;
	int		in_double;

	i = 0;
	single_count = 0;
	double_count = 0;
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
	if (single_count % 2 == 0 && double_count % 2 == 0)
		return (1);
	else
		return (0);
}

char	*process_quotes_and_expand(char *input, t_req *res)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		start;
	char	c[2];

	result = ft_strdup("");
	i = 0;
	if (!input)
		return (result);
	if (!validate_quotes(input))
		return (free(result), NULL);
	while (input[i])
	{
		if (input[i] == '\'')
		{
			start = ++i;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i])
			{
				temp = ft_substr(input, start, i - start);
				expanded = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = expanded;
				i++;
			}
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
			{
				if (input[i] == '$')
				{
					temp = expand_token_var(input, &i, res);
					expanded = ft_strjoin(result, temp);
					free(result);
					free(temp);
					result = expanded;
				}
				else
				{
					c[0] = input[i++];
					c[1] = '\0';
					temp = ft_strjoin(result, c);
					free(result);
					result = temp;
				}
			}
			if (input[i] == '"')
				i++;
		}
		else if (input[i] == '$')
		{
			temp = expand_token_var(input, &i, res);
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = expanded;
		}
		else
		{
			c[0] = input[i++];
			c[1] = '\0';
			temp = ft_strjoin(result, c);
			free(result);
			result = temp;
		}
	}
	return (result);
}

int	check_valid_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}
