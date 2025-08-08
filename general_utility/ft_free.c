/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/09 00:15:39 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_double_free(char ***ptr)
{
	int	i;

	if (!ptr || !*ptr)
		return ;
	i = 0;
	while ((*ptr)[i])
		free((*ptr)[i++]);
	free(*ptr);
	*ptr = NULL;
}

void	free_cmds(t_list *cmds)
{
	t_list	*tmp;
	t_cmd	*cmd;

	while (cmds)
	{
		tmp = cmds->next;
		cmd = (t_cmd *)cmds->content;
		if (cmd)
		{
			if (cmd->infile >= 0 && cmd->infile != STDIN_FILENO)
			{
				close(cmd->infile);
				cmd->infile = -1;
			}
			if (cmd->outfile >= 0 && cmd->outfile != STDOUT_FILENO)
			{
				close(cmd->outfile);
				cmd->outfile = -1;
			}
			ft_double_free(&cmd->full_cmd);
			free(cmd->full_path);
			free_redirects(cmd->redirects);
			free(cmd);
		}
		free(cmds);
		cmds = tmp;
	}
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_all(t_req *req)
{
	if (!req)
		return ;
	if (req->envp)
		ft_double_free(&req->envp);
	if (req->export_list)
		ft_double_free(&req->export_list);
	if (req->cmds)
	{
		free_cmds(req->cmds);
		req->cmds = NULL;
	}
	if (req->tokens)
	{
		free_string_array(req->tokens);
		req->tokens = NULL;
	}
}
