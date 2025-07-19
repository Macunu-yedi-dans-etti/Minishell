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
			t_process_data *data)
{
	char	*expanded;

	expanded = process_variable(input, i, data->envp, data->req);
	if (!expanded)
		return (free(result), NULL);
	result = append_str(result, expanded, data->len);
	free(expanded);
	return (result);
}

static void	setup_data(t_process_data *data, char **envp, t_req *req, int *len)
{
	data->envp = envp;
	data->req = req;
	data->len = len;
}

char	*process_input_loop(const char *input, char **envp, t_req *req)
{
	int				i;
	int				len;
	char			*result;
	t_process_data	data;

	i = 0;
	len = 1;
	setup_data(&data, envp, req, &len);
	result = initialize_result();
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = handle_dollar_sign(result, input, &i, &data);
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
