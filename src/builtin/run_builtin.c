/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:23:04 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:20 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_builtin(t_pipeline_data *data)
{
	if (!ft_strncmp(data->current_cmd->full_cmd[0], "echo", 5))
		return (builtin_echo(data));
	else if (!ft_strncmp(data->current_cmd->full_cmd[0], "pwd", 4))
		return (builtin_pwd(data));
	else if (!ft_strncmp(data->current_cmd->full_cmd[0], "cd", 3))
		return (builtin_cd(data));
	else if (!ft_strncmp(data->current_cmd->full_cmd[0], "export", 7))
		return (builtin_export(data));
	else if (!ft_strncmp(data->current_cmd->full_cmd[0], "unset", 6))
		return (builtin_unset(data));
	else if (!ft_strncmp(data->current_cmd->full_cmd[0], "exit", 5))
		return (builtin_exit(data));
	else
		return (-1);
}

int	run_builtin(t_pipeline_data *data)
{
	int	ret;

	if (!data->current_cmd || !data->current_cmd->full_cmd
		|| !data->current_cmd->full_cmd[0])
	{
		data->req->exit_stat = 1;
		return (1);
	}
	ret = handle_builtin(data);
	if (ret == -1)
	{
		ms_error(ERR_NO_CMD, data->current_cmd->full_cmd[0], 1, data->req);
		data->req->exit_stat = 127;
		return (127);
	}
	data->req->exit_stat = ret;
	return (ret);
}
