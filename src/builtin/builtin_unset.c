/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:22:13 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 03:50:00 by musoysal         ###   ########.fr       */
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

int	builtin_unset(char **args, t_req *req)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_code = 1;
		}
		else
			mini_unsetenv(&req->envp, args[i]);
		i++;
	}
	g_exit_status = exit_code;
	return (exit_code);
}
