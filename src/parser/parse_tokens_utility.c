/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utility.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:14:56 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/17 19:14:56 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_parse_result handle_process_result(t_parse_result result, t_req *req, int *i, int *has_cmd)
{
	if (result == PARSE_ERROR)
	{
		free_cmd(req->cur_cmd);
		req->cur_cmd = NULL;
		return PARSE_ERROR;
	}
	else if (result == PARSE_PIPE)
	{
		*has_cmd = 1;
		(*i)++;
	}
	else if (result == PARSE_REDIRECT)
		return PARSE_CONTINUE;
	else
		(*i)++;
	return -1;
}

static int	check_heredoc_and_free(t_req *req)
{
	if (req->heredoc_interrupted)
	{
		free_cmd(req->cur_cmd);
		req->cur_cmd = NULL;
		return (1);
	}
	return (0);
}

t_parse_result process_command_tokens(int *i, t_req *req, int status)
{
	int	has_cmd;
	t_parse_result result;

	req->cur_cmd = init_cmd();
	if (!req->cur_cmd)
		return (1);
	has_cmd = 0;
	while (req->tokens[*i] && ft_strncmp(req->tokens[*i], "|", 2))
	{
		if (check_heredoc_and_free(req))
			return (1);
		result = handle_token_processing(i, req);
		status = handle_process_result(result, req, i, &has_cmd);
		if (status == PARSE_ERROR)
			return PARSE_ERROR;
		if (status == PARSE_CONTINUE)
			continue ;
	}
	if (!has_cmd)
	{
		free_cmd(req->cur_cmd);
		req->cur_cmd = NULL;
		return PARSE_PIPE;
	}
	return PARSE_OK;
}

void	set_command_path(t_cmd *cmd, t_req *req)
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

int	handle_pipe_processing(int *i, t_req *req)
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
