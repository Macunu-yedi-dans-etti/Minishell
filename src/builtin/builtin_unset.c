/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:22:13 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:22:28 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_unset(char **args, t_req *req)
{
	int	i;

	i = 1;
	while (args[i])
	{
		mini_unsetenv(&req->envp, args[i]);
		i++;
	}
	return (0);
}
