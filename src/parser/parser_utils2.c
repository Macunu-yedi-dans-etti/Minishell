/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 10:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/utilities.h"

static int	handle_empty_command(t_token **tokens, int *i, t_list **cmds,
		t_req *req)
{
	if (tokens[*i] && tokens[*i]->str
		&& !ft_strncmp(tokens[*i]->str, "|", 2))
	{
		(*i)++;
		if (!tokens[*i])
		{
			ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
			free_cmds(*cmds);
			return (1);
		}
	}
	return (0);
}

static int	handle_pipe_transition(t_token **tokens, int *i, t_list **cmds,
		t_req *req)
{
	if (tokens[*i] && tokens[*i]->str && !ft_strncmp(tokens[*i]->str, "|", 2))
	{
		(*i)++;
		if (!tokens[*i])
		{
			ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
			free_cmds(*cmds);
			return (1);
		}
	}
	return (0);
}

int	process_empty_cmd_case(t_token **tokens, int *i, t_list **cmds, t_req *req)
{
	return (handle_empty_command(tokens, i, cmds, req));
}

int	process_pipe_case(t_token **tokens, int *i, t_list **cmds, t_req *req)
{
	return (handle_pipe_transition(tokens, i, cmds, req));
}
