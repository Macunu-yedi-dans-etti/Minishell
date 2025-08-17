/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (ms_error(ERR_ALLOC, "t_cmd", 1, NULL), NULL);
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redirect(const char *token)
{
	if (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

void	cleanup_and_return(t_req *req)
{
	if (req->cur_cmd)
	{
		free_cmd(req->cur_cmd);
		req->cur_cmd = NULL;
	}
	if (req->cmds)
	{
		free_cmds(req->cmds);
		req->cmds = NULL;
	}
}

void	add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*current;

	new_cmd->next = NULL;
	if (!*list)
	{
		*list = new_cmd;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

int	parse_syntax_check(t_req *req)
{
	if (!req->tokens || !req->tokens[0]
		|| !ft_strncmp(req->tokens[0], "|", 2))
	{
		if (req->tokens && req->tokens[0]
			&& !ft_strncmp(req->tokens[0], "|", 2))
			ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
		req->cmds = NULL;
		return (1);
	}
	return (0);
}
