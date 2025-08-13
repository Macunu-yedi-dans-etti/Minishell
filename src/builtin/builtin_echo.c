/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:23 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/13 12:58:09 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_pipeline_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (data->current_cmd->full_cmd[i]
		&& is_valid_n_flag(data->current_cmd->full_cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (data->current_cmd->full_cmd[i])
	{
		if (data->current_cmd->full_cmd[i])
			ft_putstr_fd(data->current_cmd->full_cmd[i], STDOUT_FILENO);
		if (data->current_cmd->full_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	if (data->req)
		data->req->exit_stat = 0;
	return (0);
}
