/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:29:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:37:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_shell	*init_cmd(void)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	if (!cmd)
		return (NULL);
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

static int	set_redirection(t_shell *cmd, t_token **tokens, int *i)
{
	char	*redir;

	redir = tokens[*i]->str;
	(*i)++;
	if (!tokens[*i])
		return (1);
	if (!ft_strncmp(redir, "<", 2))
		cmd->infile_path = ft_strdup(tokens[*i]->str);
	else if (!ft_strncmp(redir, ">", 2))
	{
		cmd->outfile_path = ft_strdup(tokens[*i]->str);
		cmd->append_out = 0;
	}
	else if (!ft_strncmp(redir, ">>", 3))
	{
		cmd->outfile_path = ft_strdup(tokens[*i]->str);
		cmd->append_out = 1;
	}
	else if (!ft_strncmp(redir, "<<", 3))
	{
		cmd->infile = handle_heredoc(tokens[*i]->str);
		if (cmd->infile < 0)
			return (1);
	}
	(*i)++;
	return (0);
}

t_list	*parse_tokens(t_token **tokens, t_req *req)
{
	int		i;
	t_list	*cmds;
	t_shell	*current;

	i = 0;
	cmds = NULL;
	(void)req;
	while (tokens[i])
	{
		current = init_cmd();
		if (!current)
			return (NULL);
		while (tokens[i] && ft_strncmp(tokens[i]->str, "|", 2))
		{
			if (is_redirect(tokens[i]->str))
			{
				if (set_redirection(current, tokens, &i))
					return (free_cmds(cmds), NULL);
			}
			else
				current->full_cmd = ft_double_extension(current->full_cmd,
					tokens[i++]->str);
		}
		ft_lstadd_back(&cmds, ft_lstnew(current));
		if (tokens[i])
			i++;
	}
	return (cmds);
}
