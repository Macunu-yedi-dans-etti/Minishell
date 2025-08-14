/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_exit_status(int *i, t_req *req)
{
	(*i)++;
	if (req)
		return (ft_itoa(req->exit_stat));
	else
		return (ft_itoa(0));
}

static char	*handle_var_expansion(const char *input, int *i,
								char **envp, t_req *req)
{
	int		var_len;
	char	*var_name;
	char	*value;
	char	*result;

	var_len = get_var_len(&input[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(input, *i, var_len);
	*i += var_len;
	if (!var_name)
	{
		if (req)
			req->exit_stat = 1;
		return (ft_strdup(""));
	}
	value = mini_getenv(var_name, envp, -1);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	result = ft_strdup(value);
	free(value);
	return (result);
}

char	*expand_var(const char *input, int *i, char **envp, t_req *req)
{
	(*i)++;
	if (input[*i] == '?')
		return (handle_exit_status(i, req));
	return (handle_var_expansion(input, i, envp, req));
}
