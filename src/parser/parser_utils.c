/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 10:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/utilities.h"

t_shell	*init_cmd(t_req *req)
{
	t_shell	*cmd;

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

void	add_redirect(t_shell *cmd, t_redirect_type type, char *filename)
{
	t_redirect	*new_redir;
	t_redirect	*current;

	new_redir = malloc(sizeof(t_redirect));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
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
}

int	is_redirect(const char *token)
{
	if (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->filename);
		free(redir);
		redir = next;
	}
}
