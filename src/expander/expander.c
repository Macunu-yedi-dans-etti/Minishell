/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/02 21:18:37 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	should_escape_char(const char *input, int i, int quote)
{
	return (input[i] == '\\' && quote == 2
		&& (input[i + 1] == '"' || input[i + 1] == '$'
			|| input[i + 1] == '\\'));
}
/*
Input: "Hello \"$USER\""

Position 7: input[7] = '\'  input[8] = '"'
should_escape_char(input, 7, 2) → true
// Backslash skip edilir, sonraki " literal olarak alınır

Position 9: input[9] = '$'  (literal " sonrası)
// Normal variable expansion

Position 15: input[15] = '\'  input[16] = '"'  
should_escape_char(input, 15, 2) → true
// Son quote da escape edilir
*/

char	*expand_str(const char *input, char **envp, int quote, t_req *req)// expand_str(trimmed_output, res->envp, QUOTE_NONE, res);
{
	if (!input)
		return (NULL);
	if (quote == 1)//tek tırnak olsaydı expanda gerek yok
		return (ft_strdup(input));
	return (process_input_loop(input, envp, req));
}
