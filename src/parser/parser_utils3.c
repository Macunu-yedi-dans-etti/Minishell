/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 10:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/utilities.h"

static int	handle_redir(t_shell *cmd, char *redir, char *file, t_req *req)
{
	if (!file)
	{
		ms_error(ERR_NO_DIR, "filename is NULL", 1, req);
		return (1);
	}
	if (!ft_strncmp(redir, "<", 2))
		add_redirect(cmd, R_IN, file);
	else if (!ft_strncmp(redir, ">", 2))
		add_redirect(cmd, R_OUT, file);
	else if (!ft_strncmp(redir, ">>", 3))
		add_redirect(cmd, R_APPEND, file);
	else if (!ft_strncmp(redir, "<<", 3))
		cmd->infile = handle_heredoc(file, req);
	return (0);
}

int	set_redirection(t_shell *cmd, t_token **tokens, int *i, t_req *req)
{
	char	*redir;

	redir = tokens[*i]->str;
	(*i)++;
	if (!tokens[*i])
		return (ms_error(ERR_PIPE_SYNTAX, redir, 2, req), 1);
	if (!ft_strncmp(tokens[*i]->str, "|", 2))
		return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), 1);
	if (handle_redir(cmd, redir, tokens[*i]->str, req))
		return (1);
	(*i)++;
	return (0);
}

static int	process_token_expand(t_shell *cmd, t_token *token, t_req *req)
{
	char	*expanded;

	expanded = ft_strdup(token->str);
	if (!expanded)
	{
		ms_error(ERR_ALLOC, "expanded", 1, req);
		return (1);
	}
	cmd->full_cmd = ft_double_extension(cmd->full_cmd, expanded);
	free(expanded);
	if (!cmd->full_cmd)
	{
		ms_error(ERR_ALLOC, "full_cmd", 1, req);
		return (1);
	}
	return (0);
}

int	handle_token_processing(t_shell *cmd, t_token **tokens, int *i,
		t_req *req)
{
	if (is_redirect(tokens[*i]->str))
	{
		if (set_redirection(cmd, tokens, i, req))
			return (1);
		return (3);
	}
	else if (tokens[*i]->str && (tokens[*i]->str[0] != '\0'
			|| tokens[*i]->quote != QUOTE_NONE))
	{
		if (process_token_expand(cmd, tokens[*i], req))
			return (1);
		return (2);
	}
	return (0);
}
