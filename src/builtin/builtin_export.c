/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/06 16:00:49 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	builtin_export(char **args, t_req *req)
{
	int		i;
	int		exit_code;
	char	*var_name;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return (g_exit_status = builtin_env(req->envp), g_exit_status);
	while (args[i])
	{
		var_name = get_variable_name(args[i]);
		if (!var_name || !is_valid_identifier(var_name))
		{
			print_export_error(args[i]);
			exit_code = 1;
		}
		else if (ft_strchr(args[i], '='))
			mini_setenv_line(&req->envp, args[i]);
		free(var_name);
		i++;
	}
	g_exit_status = exit_code;
	return (exit_code);
}
