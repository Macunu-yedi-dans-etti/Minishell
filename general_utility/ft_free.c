/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 12:43:21 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_double_free(char ***freee)
{
	int	i;

	i = 0;
	if (!freee || !*freee)
		return ;
	while (freee && freee[0] && freee[0][i])
	{
		free((*freee)[i]);
		i++;
	}
	free(*freee);
	*freee = NULL;
}

void	free_cmds(t_list *cmds)
{
	t_list	*tmp;
	t_shell	*cmd;

	while (cmds)
	{
		tmp = cmds->next;
		cmd = (t_shell *)cmds->content;
		if (cmd)
		{
			ft_double_free(&cmd->full_cmd);
			free(cmd->full_path);
			free(cmd);
		}
		free(cmds);
		cmds = tmp;
	}
}

void	free_all(t_req *req)
{
	if (req->envp)
		ft_double_free(&req->envp);
	// export eklenecek
}
