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

static int	handle_redir(t_cmd *cmd, char *redir, char *file, t_req *req)
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
	{
		if (req && req->heredoc_interrupted)
			return (1);
		cmd->infile = handle_heredoc(file, req);
		if (req && req->heredoc_interrupted)
			return (1);
	}
	return (0);
}

int	set_redirection(t_cmd *cmd, char **tokens, int *i, t_req *req)
{
	char	*redir;

	redir = tokens[*i];
	(*i)++;
	if (!tokens[*i])
		return (ms_error(ERR_PIPE_SYNTAX, redir, 2, req), 1);
	if (!ft_strncmp(tokens[*i], "|", 2))
		return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), 1);
	if (handle_redir(cmd, redir, tokens[*i], req))
		return (1);
	(*i)++;
	return (0);
}

static int	process_token_expand(t_cmd *cmd, char *token, t_req *req)
{
	char	*expanded;
	char	**old_full_cmd;

	// Eğer komut henüz belirlenmemişse ve token boş string ise atla
	if (!cmd->full_cmd && token[0] == '\0')
		return (0);
		
	expanded = ft_strdup(token);
	if (!expanded)
	{
		ms_error(ERR_ALLOC, "expanded", 1, req);
		return (1);
	}
	old_full_cmd = cmd->full_cmd;
	cmd->full_cmd = ft_double_extension(cmd->full_cmd, expanded);
	free(expanded);
	if (!cmd->full_cmd)
	{
		// Restore old state if allocation failed
		cmd->full_cmd = old_full_cmd;
		ms_error(ERR_ALLOC, "full_cmd", 1, req);
		return (1);
	}
	return (0);
}

int	handle_token_processing(t_cmd *cmd, char **tokens, int *i,
		t_req *req)
{
	if (is_redirect(tokens[*i]))
	{
		if (set_redirection(cmd, tokens, i, req))
			return (1);
		return (3);
	}
	else if (tokens[*i])
	{
		if (process_token_expand(cmd, tokens[*i], req))
			return (1);
		// Eğer komut henüz belirlenmemişse ve token boş string ise has_cmd set etme
		if (!cmd->full_cmd && tokens[*i][0] == '\0')
			return (0);
		return (2);
	}
	return (0);
}
