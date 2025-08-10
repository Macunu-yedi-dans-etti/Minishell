/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:09 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/10 19:15:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_cmd(t_cmd *cmd)
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
	t_cmd *next;

	while (cmds)
	{
		next = cmds->next;
		free_cmd(cmds);
		cmds = next;
	}
}

void	free_req(t_req *req)
{
	if (!req)
		return ;
	if (req->envp)
		ft_double_free(&req->envp);
	if (req->export_list)
		ft_double_free(&req->export_list);
	if (req->tokens)
		ft_double_free(&req->tokens);
}

void	free_all(t_pipeline_data *data)
{
	if (!data || !data->req)
		return ;
	free_req(data->req);
	if (data->req->cmds)
	{
		free_cmds(data->req->cmds);
		data->req->cmds = NULL;
	}
}
