/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:29:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 21:29:51 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/utilities.h"

static t_shell	*process_command_tokens(t_token **tokens, int *i, t_req *req)
{
	t_shell	*cmd;
	int		has_cmd;
	int		result;

	cmd = init_cmd(req);
	if (!cmd)
		return (NULL);
	has_cmd = 0;
	while (tokens[*i] && (ft_strncmp(tokens[*i]->str, "|", 2)
			|| tokens[*i]->quote != QUOTE_NONE))
	{
		result = handle_token_processing(cmd, tokens, i, req);
		if (result == 1)
			return (free(cmd), NULL);
		else if (result == 2)
		{
			has_cmd = 1;
			(*i)++;
		}
		else if (result == 3)
		{
			continue;
		}
		else
			(*i)++;
	}
	if (!has_cmd)
		return (free(cmd), NULL);
	return (cmd);
}

static void	set_command_path(t_shell *cmd, t_req *req)
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

t_list	*parse_tokens(t_token **tokens, t_req *req)
{
	t_list	*cmds;
	t_shell	*current;
	int		i;

	cmds = NULL;
	i = 0;
	if (!tokens || !tokens[0])
		return (NULL);
	if (!ft_strncmp(tokens[0]->str, "|", 2))
		return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), NULL);
	while (tokens[i])
	{
		current = process_command_tokens(tokens, &i, req);
		if (!current)
		{
			if (process_empty_cmd_case(tokens, &i, &cmds, req))
				return (NULL);
			continue;
		}
		set_command_path(current, req);
		ft_lstadd_back(&cmds, ft_lstnew(current));
		if (process_pipe_case(tokens, &i, &cmds, req))
			return (NULL);
	}
	return (cmds);
}
