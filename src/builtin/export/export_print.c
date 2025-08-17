/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/17 17:41:07 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

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

static void	print_export_variable(char *var)
{
	char	*eq;

	eq = ft_strchr(var, '=');
	if (eq)
	{
		write(1, "declare -x ", 11);
		write(1, var, eq - var);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, "declare -x ", 11);
		ft_putendl_fd(var, 1);
	}
}

void	print_sorted_export(char **envp, char **export_list)
{
	char	**merged;
	int		i;

	merged = merge_env_export(envp, export_list);
	if (!merged)
		return ;
	sort_str_array(merged);
	i = 0;
	while (merged[i])
	{
		print_export_variable(merged[i]);
		i++;
	}
	ft_free_array(merged);
}
