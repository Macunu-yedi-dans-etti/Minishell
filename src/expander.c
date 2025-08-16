/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:09:56 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 22:09:56 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_special_vars(char *str, int *i, t_req *res)
{
	char	*value;
	char	*dup;

	if (str[*i] == '?')
		return ((*i)++, ft_itoa(res->exit_stat));
	if (str[*i] == '$')
		return ((*i)++, ft_itoa(getpid()));
	if (str[*i] == '_')
	{
		(*i)++;
		value = mini_getenv("_", res->envp, 1);
		if (!value)
			return (ft_strdup(""));
		dup = ft_strdup(value);
		free(value);
		return (dup);
	}
	return (NULL);
}

static int	is_var_char(int c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static char	*expand_quotes_case(char *str, int *i)
{
	if (str[*i] == '"' || str[*i] == '\'')
	{
		if (str[*i + 1] && (str[*i + 1] == '"' || str[*i + 1] == '\''))
		{
			(*i) += 2;
			return (ft_strdup(""));
		}
		return (ft_strdup("$"));
	}
	return (NULL);
}

static char	*expand_env_var(char *str, int *i, t_req *res)
{
	int		start;
	char	*name;
	char	*value;
	char	*dup;

	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	value = mini_getenv(name, res->envp, 1);
	free(name);
	if (!value)
		return (ft_strdup(""));
	dup = ft_strdup(value);
	free(value);
	return (dup);
}

char	*expand_token_var(char *str, int *i, t_req *res)
{
	char	*spec;
	char	*quote;

	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	quote = expand_quotes_case(str, i);
	if (quote)
		return (quote);
	spec = expand_special_vars(str, i, res);
	if (spec)
		return (spec);
	return (expand_env_var(str, i, res));
}
