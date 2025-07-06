/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:29:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 04:37:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exit_status;

static t_shell	*init_cmd(void)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	if (!cmd)
	{
		ms_error(ERR_ALLOC, "t_shell", 1);
		return (NULL);
	}
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->infile_path = NULL;
	cmd->outfile_path = NULL;
	cmd->append_out = 0;
	return (cmd);
}

static int	is_redirect(const char *token)
{
	return (!ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3)
		|| !ft_strncmp(token, "<<", 3));
}

static int	handle_redir(t_shell *cmd, char *redir, char *file)
{
	if (!ft_strncmp(redir, "<", 2))
	{
		cmd->infile_path = ft_strdup(file);
		if (!cmd->infile_path)
			return (ms_error(ERR_ALLOC, "infile_path", 1), 1);
	}
	else if (!ft_strncmp(redir, ">", 2))
	{
		cmd->outfile_path = ft_strdup(file);
		cmd->append_out = 0;
		if (!cmd->outfile_path)
			return (ms_error(ERR_ALLOC, "outfile_path", 1), 1);
	}
	else if (!ft_strncmp(redir, ">>", 3))
	{
		cmd->outfile_path = ft_strdup(file);
		cmd->append_out = 1;
		if (!cmd->outfile_path)
			return (ms_error(ERR_ALLOC, "outfile_path", 1), 1);
	}
	else if (!ft_strncmp(redir, "<<", 3))
	{
		cmd->infile = handle_heredoc(file);
		if (cmd->infile < 0)
			return (ms_error(ERR_HEREDOC, file, 1), 1);
	}
	return (0);
}

static int	set_redirection(t_shell *cmd, t_token **tokens, int *i)
{
	char	*redir;

	redir = tokens[*i]->str;
	(*i)++;
	if (!tokens[*i])
		return (ms_error(ERR_PIPE_SYNTAX, redir, 2), 1);
	if (handle_redir(cmd, redir, tokens[*i]->str))
		return (1);
	(*i)++;
	return (0);
}

t_list	*parse_tokens(t_token **tokens, t_req *req)
{
	t_list	*cmds;
	t_shell	*current;
	int		i;

	(void)req;
	cmds = NULL;
	i = 0;
	if (!tokens || !tokens[0])
		return (NULL);
	while (tokens[i])
	{
		current = init_cmd();
		if (!current)
			return (ms_error(ERR_ALLOC, "command", 1), NULL);
		while (tokens[i] && ft_strncmp(tokens[i]->str, "|", 2))
		{
			if (is_redirect(tokens[i]->str))
			{
				if (set_redirection(current, tokens, &i))
					return (free_cmds(cmds), NULL);
			}
			else
			{
				current->full_cmd = ft_double_extension(current->full_cmd,
						tokens[i]->str);
				i++;
			}
		}
		ft_lstadd_back(&cmds, ft_lstnew(current));
		if (tokens[i])
			i++;
	}
	return (cmds);
}
