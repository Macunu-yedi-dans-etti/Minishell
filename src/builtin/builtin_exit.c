/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:59:54 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/20 20:18:54 by haloztur         ###   ########.fr       */
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

int	builtin_exit(char **args, t_req *req)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			rl_clear_history();
			if (req)
				free_all(req);
			ms_error(ERR_NO_CMD, "exit: numeric argument required", 2, req);
			exit(2);
		}
		if (args[2])
		{
			ms_error(ERR_NO_CMD, "exit: too many arguments", 1, req);
			if (req)
				req->exit_stat = 1;
			return (1);
		}
		if (req)
			req->exit_stat = ft_atoi(args[1]);
	}
	rl_clear_history();
	if (req)
	{
		free_all(req);
		exit(req->exit_stat);
	}
	else
		exit(0);
}
