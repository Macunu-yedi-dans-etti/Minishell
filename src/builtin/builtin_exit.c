/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:59:54 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/09 00:25:33 by haloztur         ###   ########.fr       */
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
			ms_error(ERR_EMPTY, "exit: numeric argument required", 2, req);
			if (req)
			{
				req->exit_stat = 2;
				req->should_exit = 1;
				// rl_clear_history();
				// free_all(req);
			}
			return (2);
		}
		if (args[2])
		{
			ms_error(ERR_EMPTY, "exit: too many arguments", 1, req);
			if (req)
				req->exit_stat = 1;
			return (1);
		}
		if (req)
			req->exit_stat = ft_atoi(args[1]) & 255;
	}
	else if (req)
		req->exit_stat = 0;
	if (req)
		req->should_exit = 1;
	return (req ? req->exit_stat : 0);
}
