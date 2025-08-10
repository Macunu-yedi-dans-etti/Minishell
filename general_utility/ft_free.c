/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/10 15:40:07 by musoysal         ###   ########.fr       */
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

static void	free_single_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
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

void	free_cmds(t_cmd *cmds)
{
	// iterate over direct t_cmd linked list
	while (cmds)
	{
		t_cmd *next = cmds->next;
		free_single_cmd(cmds);
		cmds = next;
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
