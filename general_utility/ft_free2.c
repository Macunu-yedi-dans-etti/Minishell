/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:23:40 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/17 19:24:22 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_pipeline_data *data)
{
	if (!data)
		return ;
	if (data->req)
	{
		if (data->req->cmds)
		{
			free_cmds(data->req->cmds);
			data->req->cmds = NULL;
		}
		if (data->req->cur_cmd)
		{
			free_cmd(data->req->cur_cmd);
			data->req->cur_cmd = NULL;
		}
		free_req(data->req);
	}
}
