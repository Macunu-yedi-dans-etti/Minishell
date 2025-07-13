/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:28:41 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 14:33:48 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_cd_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

static char	*try_expand_tilde(char *arg, t_req *req)
{
	char	*home;
	char	*result;

	if (arg[0] != '~')
		return (NULL);
	home = mini_getenv("HOME", req->envp, 4);
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		result = ft_strdup(home);
	else if (arg[1] == '/')
		result = ft_strjoin(home, arg + 1);
	else
		result = NULL;
	free(home);
	return (result);
}

static char	*get_cd_target_from_env(t_shell *cmd, t_req *req, int *need_free)
{
	char	*target;

	if (!cmd->full_cmd[1])
	{
		target = mini_getenv("HOME", req->envp, 4);
		if (target != NULL)
			*need_free = 1;
		return (target);
	}
	if (!ft_strncmp(cmd->full_cmd[1], "-", 2))
	{
		target = mini_getenv("OLDPWD", req->envp, 6);
		if (target)
		{
			ft_putendl_fd(target, STDOUT_FILENO);
			*need_free = 1;
		}
		return (target);
	}
	return (NULL);
}

char	*get_cd_target(t_shell *cmd, t_req *req, int *need_free)
{
	char	*target;
	char	*expanded;

	*need_free = 0;
	target = get_cd_target_from_env(cmd, req, need_free);
	if (target)
		return (target);
	if (cmd->full_cmd[1] && cmd->full_cmd[1][0] == '~')
	{
		expanded = try_expand_tilde(cmd->full_cmd[1], req);
		if (expanded)
		{
			*need_free = 1;
			return (expanded);
		}
		return (cmd->full_cmd[1]);
	}
	if (cmd->full_cmd[1])
		return (cmd->full_cmd[1]);
	return (NULL);
}
