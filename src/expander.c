/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:09:05 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/15 23:09:05 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_special_vars(char *str, int *i, t_req *res)
{
	char	*value;
	char	*dup;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(res->exit_stat));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_itoa(getpid()));
	}
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
	return (ft_isalnum(c) || c == '_');
}

char	*expand_token_var(char *str, int *i, t_req *res)
{
	int     start;
	char    *name;
	char    *value;
	char    *special;
	char    *dup;

	(*i)++;
	if (str[*i] == '"' || str[*i] == '\'')
		return (ft_strdup(""));
	if (!str[*i])
		return (ft_strdup("$"));
	special = expand_special_vars(str, i, res);
	if (special)
		return (special);
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	value = mini_getenv(name, res->envp, 1);
	if (!value)
		return (free(name), ft_strdup(""));
	dup = ft_strdup(value);
	return (free(name), free(value), dup);
}
