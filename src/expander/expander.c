/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:26:57 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	should_escape_char(const char *input, int i, int quote)
{
	return (input[i] == '\\' && quote == 2
		&& (input[i + 1] == '"' || input[i + 1] == '$'
			|| input[i + 1] == '\\'));
}

char	*expand_str(const char *input, char **envp, int quote, t_req *req)
{
	if (!input)
		return (NULL);
	if (quote == 1)
		return (ft_strdup(input));
	return (process_input_loop(input, envp, req));
}
