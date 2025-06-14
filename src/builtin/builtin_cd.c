/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:19:50 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:20:01 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(char **args, char **envp)
{
	char	*path;

	path = args[1];
	if (!path)
		path = mini_getenv("HOME", envp, 4);
	if (!path || chdir(path) != 0)
	{
		perror("cd");
		if (!args[1])
			free(path);
		return (1);
	}
	if (!args[1])
		free(path);
	return (0);
}
