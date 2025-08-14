/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*process_variable(const char *input, int *i, char **envp,
			t_req *req)
{
	char	*expanded;

	expanded = expand_var(input, i, envp, req);
	if (!expanded)
		return (NULL);
	return (expanded);
}

static char	*process_character(char *result, const char *input, int *i,
			int *len)
{
	if (should_escape_char(input, *i, 2))
		(*i)++;
	result = append_char(result, input[(*i)++], len);
	return (result);
}

static char	*handle_dollar_sign(char *result, const char *input, int *i,
			char **envp, t_req *req, int *len)
{
	char	*expanded;

	expanded = process_variable(input, i, envp, req);
	if (!expanded)
		return (free(result), NULL);
	result = append_str(result, expanded, len);
	free(expanded);
	return (result);
}

char	*process_input_loop(const char *input, char **envp, t_req *req)
{
	int				i;
	int				len;
	char			*result;

	i = 0;
	len = 1;
	result = initialize_result();
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = handle_dollar_sign(result, input, &i, envp, req, &len);
			if (!result)
				return (NULL);
			continue ;
		}
		result = process_character(result, input, &i, &len);
		if (!result)
			return (NULL);
	}
	return (result);
}
