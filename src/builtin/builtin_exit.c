/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:59:54 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/15 14:06:08 by haloztur         ###   ########.fr       */
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

int	builtin_exit(char **args)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ms_error(ERR_NO_CMD, "exit: numeric argument required", 2);
			exit(2);
		}
		if (args[2])
		{
			ms_error(ERR_NO_CMD, "exit: too many arguments", 1);
			g_exit_status = 1;
			return (1);
		}
		g_exit_status = ft_atoi(args[1]);
	}
	exit(g_exit_status);
}

