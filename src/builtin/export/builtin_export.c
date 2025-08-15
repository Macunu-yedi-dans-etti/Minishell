/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/15 12:07:25 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_valid_identifier_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!is_valid_identifier_char(str[0], 1))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_valid_identifier_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

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

static int	str_in_array(char **arr, char *str)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	add_to_export_list(char ***export_list, char *var)
{
	int		len;
	int		i;
	char	**new_list;

	if (str_in_array(*export_list, var))
		return ;
	len = 0;
	while (*export_list && (*export_list)[len])
		len++;
	new_list = malloc(sizeof(char *) * (len + 2));
	if (!new_list)
		return ;
	i = 0;
	while (i < len)
	{
		new_list[i] = (*export_list)[i];
		i++;
	}
	new_list[len] = ft_strdup(var);
	new_list[len + 1] = NULL;
	free(*export_list);
	*export_list = new_list;
}

static void	remove_from_export_list(char ***export_list, char *var)
{
	int		i;
	int		j;
	int		len;
	char	**new_list;

	len = 0;
	while (*export_list && (*export_list)[len])
		len++;
	new_list = malloc(sizeof(char *) * (len + 1));
	if (!new_list)
		return ;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp((*export_list)[i], var, ft_strlen(var)) != 0)
			new_list[j++] = (*export_list)[i];
		else
			free((*export_list)[i]);
		i++;
	}
	new_list[j] = NULL;
	free(*export_list);
	*export_list = new_list;
}

size_t	ft_strarrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

static char	**merge_env_export(char **envp, char **export_list)
{
	int		env_count;
	int		exp_count;
	int		i;
	int		j;
	char	**merged;

	env_count = ft_strarrlen(envp);
	exp_count = ft_strarrlen(export_list);
	merged = malloc(sizeof(char *) * (env_count + exp_count + 1));
	if (!merged)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		merged[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 0;
	while (export_list && export_list[j])
	{
		merged[i + j] = ft_strdup(export_list[j]);
		j++;
	}
	merged[i + j] = NULL;
	return (merged);
}

static void	sort_str_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr && arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	print_sorted_export(char **envp, char **export_list)
{
	char	**merged;
	int		i;
	char	*eq;

	merged = merge_env_export(envp, export_list);
	if (!merged)
		return ;
	sort_str_array(merged);
	i = 0;
	while (merged[i])
	{
		eq = ft_strchr(merged[i], '=');
		if (eq)
		{
			write(1, "declare -x ", 11);
			write(1, merged[i], eq - merged[i]);
			write(1, "=\"", 2);
			ft_putstr_fd(eq + 1, 1);
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, "declare -x ", 11);
			ft_putendl_fd(merged[i], 1);
		}
		i++;
	}
	ft_free_array(merged);
}

int	builtin_export(t_pipeline_data *data)
{
	int		i;
	int		exit_code;
	char	*var_name;

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
		var_name = get_variable_name(data->current_cmd->full_cmd[i]);
		if (!var_name || !is_valid_identifier(var_name))
		{
			print_export_error(data->current_cmd->full_cmd[i]);
			exit_code = 1;
		}
		else
		{
			if (ft_strchr(data->current_cmd->full_cmd[i], '='))
			{
				mini_setenv_line(&data->req->envp,
					data->current_cmd->full_cmd[i], data->req);
				remove_from_export_list(&data->req->export_list, var_name);
			}
			else
				add_to_export_list(&data->req->export_list, var_name);
		}
		free(var_name);
		i++;
	}
	data->req->exit_stat = exit_code;
	return (exit_code);
}
