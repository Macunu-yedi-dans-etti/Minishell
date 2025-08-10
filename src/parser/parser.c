/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:29:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 
#include "../../includes/utilities.h"

static t_cmd	*process_command_tokens(int *i, t_req *req)
{
	t_cmd	*cmd;
	int		has_cmd;
	int		result;

	cmd = init_cmd(req);
	if (!cmd)
		return (NULL);
	has_cmd = 0;
	while (req->tokens[*i] && (ft_strncmp(req->tokens[*i], "|", 2)))
	{
		if (req->heredoc_interrupted)
		{
			free_cmd(cmd);
			return (NULL);
		}
		result = handle_token_processing(cmd, i, req);
		if (result == 1)
		{
			free_cmd(cmd);
			return (NULL);
		}
		else if (result == 2)
		{
			has_cmd = 1;
			(*i)++;
		}
		else if (result == 3)
			continue;
		else
			(*i)++;
	}
	if (!has_cmd)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static void	set_command_path(t_cmd *cmd, t_req *req)
{
	char	*trimmed;

	if (!cmd->full_path && cmd->full_cmd && !is_builtin(cmd->full_cmd[0]))
	{
		trimmed = ft_strtrim(cmd->full_cmd[0], " \t");
		if (trimmed)
		{
			free(cmd->full_cmd[0]);
			cmd->full_cmd[0] = trimmed;
		}
		cmd->full_path = resolve_path(cmd->full_cmd[0], req->envp);
	}
}

static void	add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*current;

	new_cmd->next = NULL;
	if (!*list)
	{
		*list = new_cmd;
		return;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

static int	handle_pipe_processing(int *i, t_req *req)
{
	if (req->tokens[*i] && !ft_strncmp(req->tokens[*i], "|", 2))
	{
		(*i)++;
		if (!req->tokens[*i] || !ft_strncmp(req->tokens[*i], "|", 2))
		{
			ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
			return (1);
		}
	}
	return (0);
}

static void	cleanup_and_return(t_req *req)
{
	free_cmds(req->cmds);
	req->cmds = NULL;
}

void	parse_tokens(t_req *req)
{
	t_cmd	*current;
	int		i;

	if (!req->tokens || !req->tokens[0] || 
		!ft_strncmp(req->tokens[0], "|", 2))
	{
		if (req->tokens && req->tokens[0] && 
			!ft_strncmp(req->tokens[0], "|", 2))
			ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
		req->cmds = NULL;
		return;
	}
	req->cmds = NULL;
	i = 0;
	while (req->tokens[i])
	{
		if (req->heredoc_interrupted)
			return (cleanup_and_return(req));
		current = process_command_tokens(&i, req);
		if (!current)
		{
			if (req->heredoc_interrupted || handle_pipe_processing(&i, req))
				return (cleanup_and_return(req));
			continue;
		}
		set_command_path(current, req);
		add_cmd_to_list(&req->cmds, current);
		if (handle_pipe_processing(&i, req))
			return (cleanup_and_return(req));
	}
}
