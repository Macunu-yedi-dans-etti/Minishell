/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:14:07 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 22:14:07 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_process_result(int result, t_req *req, int *i, int *has_cmd)
{
	if (result == 1)
	{
		free_cmd(req->cur_cmd);
		req->cur_cmd = NULL;
		return (1);
	}
	else if (result == 2)
	{
		*has_cmd = 1;
		(*i)++;
	}
	else if (result == 3)
		return (0);
	else
		(*i)++;
	return (-1);
}

static int	process_command_tokens(int *i, t_req *req)
{
	int	has_cmd;
	int	result;
	int	status;

	req->cur_cmd = init_cmd();
	if (!req->cur_cmd)
		return (1);
	has_cmd = 0;
	while (req->tokens[*i] && ft_strncmp(req->tokens[*i], "|", 2))
	{
		if (req->heredoc_interrupted)
			return (free_cmd(req->cur_cmd), req->cur_cmd = NULL, 1);
		result = handle_token_processing(i, req);
		status = handle_process_result(result, req, i, &has_cmd);
		if (status == 1)
			return (1);
		if (status == 0)
			continue ;
	}
	if (!has_cmd)
		return (free_cmd(req->cur_cmd), req->cur_cmd = NULL, 2);
	return (0);
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

void	parse_tokens(t_req *req)
{
	int	i;
	int	res;

	if (parse_syntax_check(req))
		return ;
	i = 0;
	while (req->tokens[i])
	{
		if (req->heredoc_interrupted)
			return (cleanup_and_return(req));
		res = process_command_tokens(&i, req);
		if (res == 1)
			return (cleanup_and_return(req));
		else if (res == 2)
		{
			if (req->heredoc_interrupted || handle_pipe_processing(&i, req))
				return (cleanup_and_return(req));
			continue ;
		}
		set_command_path(req->cur_cmd, req);
		add_cmd_to_list(&req->cmds, req->cur_cmd);
		req->cur_cmd = NULL;
		if (handle_pipe_processing(&i, req))
			return (cleanup_and_return(req));
	}
}
