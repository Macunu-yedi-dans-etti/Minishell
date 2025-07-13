/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 13:55:11 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exit_status;

static int	is_env_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

static int	get_var_len(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '?')
		return (1);
	while (s[i] && is_env_char(s[i]))
		i++;
	return (i);
}

static char	*expand_var(const char *input, int *i, char **envp)
{
	int		var_len;
	char	*var_name;
	char	*value;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	var_len = get_var_len(&input[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(input, *i, var_len);
	*i += var_len;
	if (!var_name)
	{
		g_exit_status = 1;
		return (ft_strdup(""));
	}
	value = mini_getenv(var_name, envp, -1);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*append_str(char *dst, const char *src, int *len)
{
	int		src_len;
	char	*new_str;

	src_len = ft_strlen(src);
	new_str = malloc(*len + src_len);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, dst, *len - 1);
	ft_memcpy(new_str + *len - 1, src, src_len + 1);
	free(dst);
	*len += src_len;
	return (new_str);
}

static char	*append_char(char *dst, char c, int *len)
{
	char	*new_str;

	new_str = malloc(*len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, dst, *len - 1);
	new_str[*len - 1] = c;
	new_str[*len] = '\0';
	free(dst);
	(*len)++;
	return (new_str);
}

char	*expand_str(const char *input, char **envp, int quote)
{
	int		i;
	int		len;
	char	*result;
	char	*expanded;

	if (!input)
		return (NULL);
	if (quote == 1)
		return (ft_strdup(input));
	i = 0;
	len = 1;
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (input[i])
	{
		if (input[i] == '$')
		{
			expanded = expand_var(input, &i, envp);
			if (!expanded)
				return (free(result), NULL);
			result = append_str(result, expanded, &len);
			free(expanded);
			if (!result)
				return (NULL);
			continue ;
		}
		if (input[i] == '\\' && quote == 2
			&& (input[i + 1] == '"' || input[i + 1] == '$' || input[i + 1] == '\\'))
			i++;
		result = append_char(result, input[i++], &len);
		if (!result)
			return (NULL);
	}
	return (result);
}
