/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:29:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 20:17:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_shell *init_cmd(t_req *req)
{
	t_shell *cmd;

	cmd = malloc(sizeof(t_shell));
	if (!cmd)
		return (ms_error(ERR_ALLOC, "t_shell", 1, req), NULL);
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->redirects = NULL;
	return (cmd);
}

static void add_redirect(t_shell *cmd, t_redirect_type type, char *filename)
{
	t_redirect *redir = malloc(sizeof(t_redirect));
	if (!redir)
		return;
	redir->filename = ft_strdup(filename);
	redir->type = type;
	redir->next = NULL;
	t_redirect **p = &cmd->redirects;
	while (*p)
		p = &(*p)->next;
	*p = redir;
}

static int is_redirect(const char *token)
{
	return (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3));
}

static int handle_redir(t_shell *cmd, char *redir, char *file, t_req *req)
{
	if (!ft_strncmp(redir, "<", 2))
		add_redirect(cmd, R_IN, file);
	else if (!ft_strncmp(redir, ">", 2))
		add_redirect(cmd, R_OUT, file);
	else if (!ft_strncmp(redir, ">>", 3))
		add_redirect(cmd, R_APPEND, file);
	else if (!ft_strncmp(redir, "<<", 3))
		cmd->infile = handle_heredoc(file, req);
	return 0;
}

static int set_redirection(t_shell *cmd, t_token **tokens, int *i, t_req *req)
{
	char *redir;

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

void free_redirects(t_redirect *redir)
{
	t_redirect *tmp;
	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

t_list *parse_tokens(t_token **tokens, t_req *req)
{
	t_list *cmds;
	t_shell *current;
	int i;
	int has_cmd;
	char *expanded;

	cmds = NULL;
	i = 0;
	(void)req;
	if (!tokens || !tokens[0])
		return (NULL);
	if (!ft_strncmp(tokens[0]->str, "|", 2))
		return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), NULL);
	while (tokens[i])
	{
		current = init_cmd(req);
		if (!current)
			return (free_cmds(cmds), NULL);
		has_cmd = 0;
		while (tokens[i] && (ft_strncmp(tokens[i]->str, "|", 2) || tokens[i]->quote != QUOTE_NONE))
		{
			if (is_redirect(tokens[i]->str))
			{
				if (set_redirection(current, tokens, &i, req))
					return (free(current), free_cmds(cmds), NULL);
				continue;
			}
			else if (tokens[i]->str && 
					 (tokens[i]->str[0] != '\0' || tokens[i]->quote != QUOTE_NONE))
			{
				expanded = ft_strdup(tokens[i]->str);
				if (!expanded)
					return (ms_error(ERR_ALLOC, "expanded", 1, req),
							free(current), free_cmds(cmds), NULL);
				current->full_cmd = ft_double_extension(current->full_cmd, expanded);
				free(expanded);
				if (!current->full_cmd)
					return (ms_error(ERR_ALLOC, "full_cmd", 1, req),
							free(current), free_cmds(cmds), NULL);
				has_cmd = 1;
			}
			i++;
		}
		if (!has_cmd)
		{
			free(current);
			if (tokens[i] && tokens[i]->str && !ft_strncmp(tokens[i]->str, "|", 2))
			{
				i++;
				if (!tokens[i])
					return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), free_cmds(cmds), NULL);
			}
			continue;
		}
		if (!current->full_path && current->full_cmd && !is_builtin(current->full_cmd[0]))
		{
                        char *trimmed = ft_strtrim(current->full_cmd[0], " \t");
                        if (trimmed) {
                                free(current->full_cmd[0]);
                                current->full_cmd[0] = trimmed;
                        }
			current->full_path = resolve_path(current->full_cmd[0], req->envp);
		}
		ft_lstadd_back(&cmds, ft_lstnew(current));
		if (tokens[i] && tokens[i]->str && !ft_strncmp(tokens[i]->str, "|", 2))
		{
			i++;
			if (!tokens[i])
				return (ms_error(ERR_PIPE_SYNTAX, "|", 2, req), free_cmds(cmds), NULL);
		}
	}
	return (cmds);
}
