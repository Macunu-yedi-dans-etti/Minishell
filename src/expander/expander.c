/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/13 19:07:50 by musoysal         ###   ########.fr       */
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
