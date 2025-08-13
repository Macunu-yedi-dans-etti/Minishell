/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:59:54 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/13 16:18:04 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_numeric_error(t_pipeline_data *data)
{
	ms_error(ERR_EMPTY, "exit: numeric argument required", 2, data->req);
	if (data->req)
	{
		data->req->exit_stat = 2;
		data->req->should_exit = 1;
	}
}

static int	handle_exit_args(t_pipeline_data *data)
{
	if (!is_numeric(data->current_cmd->full_cmd[1]))
	{
		handle_numeric_error(data);
		return (2);
	}
	if (data->current_cmd->full_cmd[2])
	{
		ms_error(ERR_EMPTY, "exit: too many arguments", 1, data->req);
		if (data->req)
			data->req->exit_stat = 1;
		return (1);
	}
	if (data->req)
		data->req->exit_stat = ft_atoi(data->current_cmd->full_cmd[1]) & 255;
	return (-1);
}

int	builtin_exit(t_pipeline_data *data)
{
	int	result;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (data->current_cmd->full_cmd[1])
	{
		result = handle_exit_args(data);
		if (result != -1)
			return (result);
	}
	if (data->req)
		data->req->should_exit = 1;
	if (data->req)
		return (data->req->exit_stat);
	return (0);
}
