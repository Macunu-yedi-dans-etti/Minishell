/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/03 23:33:31 by haloztur         ###   ########.fr       */
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
	if (req->envp)
		ft_double_free(&req->envp);
	if (req->export_list)
		ft_double_free(&req->export_list);
	if (req->cmds)
		free_cmds(req->cmds);
	if (req->tokens)
		free_string_array(req->tokens);
}
