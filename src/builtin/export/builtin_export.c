/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 16:08:06 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "export_utils.h"

static char	*get_variable_name(char *arg)
{
	int		i;
	char	*name;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, arg, i + 1);
	return (name);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static void	process_export_arg(t_pipeline_data *data, char *arg, int *exit_code)
{
	char	*var_name;

	var_name = get_variable_name(arg);
	if (!var_name || !is_valid_identifier(var_name))
	{
		print_export_error(arg);
		*exit_code = 1;
	}
	else
	{
		if (ft_strchr(arg, '='))
		{
			mini_setenv_line(&data->req->envp, arg, data->req);
			remove_from_export_list(&data->req->export_list, var_name);
		}
		else
			add_to_export_list(&data->req->export_list, var_name, data->req->envp);
	}
	free(var_name);
}

int	builtin_export(t_pipeline_data *data)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!data->current_cmd->full_cmd[1])
	{
		print_sorted_export(data->req->envp, data->req->export_list);
		data->req->exit_stat = 0;
		return (0);
	}
	while (data->current_cmd->full_cmd[i])
	{
		process_export_arg(data, data->current_cmd->full_cmd[i], &exit_code);
		i++;
	}
	data->req->exit_stat = exit_code;
	return (exit_code);
}
