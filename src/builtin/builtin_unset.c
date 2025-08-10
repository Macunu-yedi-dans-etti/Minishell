/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:22:13 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/10 17:29:32 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_pipeline_data *data)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (data->current_cmd->full_cmd[i])
	{
		if (!is_valid_identifier(data->current_cmd->full_cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(data->current_cmd->full_cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_code = 1;
		}
		else
			mini_unsetenv(&data->req->envp, data->current_cmd->full_cmd[i]);
		i++;
	}
	data->req->exit_stat = exit_code;
	return (exit_code);
}
