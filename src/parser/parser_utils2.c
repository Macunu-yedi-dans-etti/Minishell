/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:42:53 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/15 11:42:53 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_redirect(t_cmd *cmd, t_redirect_type type, char *filename)
{
	t_redirect	*new_redir;
	t_redirect	*current;

	new_redir = malloc(sizeof(t_redirect));
	if (!new_redir)
		return (1);
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (1);
	}
	new_redir->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		current = cmd->redirects;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (0);
}

static int	handle_redir(char *redir, char *file, t_req *req)
{
	if (!file)
	{
		ms_error(ERR_NO_DIR, "filename is NULL", 1, req);
		return (1);
	}
	if (!ft_strncmp(redir, "<", 2))
		return (add_redirect(req->cur_cmd, R_IN, file));
	else if (!ft_strncmp(redir, ">", 2))
		return (add_redirect(req->cur_cmd, R_OUT, file));
	else if (!ft_strncmp(redir, ">>", 3))
		return (add_redirect(req->cur_cmd, R_APPEND, file));
	else if (!ft_strncmp(redir, "<<", 3))
	{
		if (req && req->heredoc_interrupted)
			return (1);
		req->cur_cmd->infile = handle_heredoc(file, req);
		if (req->cur_cmd->infile == -1 || (req && req->heredoc_interrupted))
			return (1);
		return (add_redirect(req->cur_cmd, R_HEREDOC, file));
	}
	return (0);
}

static int	set_redirection(int *i, t_req *req)
{
	char	*redir;

	redir = req->tokens[*i];
	(*i)++;
	if (!req->tokens[*i])
	{
		ms_error(ERR_PIPE_SYNTAX, redir, 2, req);
		return (1);
	}
	if (!ft_strncmp(req->tokens[*i], "|", 2))
	{
		ms_error(ERR_PIPE_SYNTAX, "|", 2, req);
		return (1);
	}
	if (ft_strncmp(redir, "<<", 3) && ft_strncmp(redir, ">>", 3)
		&& ft_strncmp(redir, "<", 2) && ft_strncmp(redir, ">", 2))
	{
		ms_error(ERR_PIPE_SYNTAX, redir, 2, req);
		return (1);
	}
	if (handle_redir(redir, req->tokens[*i], req))
		return (1);
	(*i)++;
	return (0);
}

static int	process_token_expand(t_cmd *cmd, char *token, t_req *req)
{
	char	*expanded;

	if (!cmd->full_cmd && token[0] == '\0')
		return (0);
	expanded = ft_strdup(token);
	if (!expanded)
	{
		ms_error(ERR_ALLOC, "expanded", 1, req);
		free(expanded);
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

t_parse_result handle_token_processing(int *i, t_req *req)
{
       if (is_redirect(req->tokens[*i]))
       {
	       if (set_redirection(i, req))
		       return PARSE_ERROR;
	       return PARSE_REDIRECT;
       }
       else if (req->tokens[*i])
       {
	       if (process_token_expand(req->cur_cmd, req->tokens[*i], req))
		       return PARSE_ERROR;
	       if (!req->cur_cmd->full_cmd && req->tokens[*i][0] == '\0')
		       return PARSE_OK;
	       return PARSE_CMD_FOUND;
       }
       return PARSE_OK;
}
