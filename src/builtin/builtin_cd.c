/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 02:24:19 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_cd_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

static char	*expand_tilde(char *arg, t_req *req)
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

static char	*get_cd_target(t_shell *cmd, t_req *req, int *need_free)
{
	char	*target;
	char	*expanded;

	*need_free = 0;
	if (!cmd->full_cmd[1])
	{
		target = mini_getenv("HOME", req->envp, 4);
		*need_free = 1;
	}
	else if (!ft_strncmp(cmd->full_cmd[1], "-", 2))
	{
		target = mini_getenv("OLDPWD", req->envp, 6);
		if (target)
			ft_putendl_fd(target, STDOUT_FILENO);
		*need_free = 1;
	}
	else if (cmd->full_cmd[1][0] == '~')
	{
		expanded = expand_tilde(cmd->full_cmd[1], req);
		if (expanded)
		{
			target = expanded;
			*need_free = 1;
		}
		else
		{
			target = cmd->full_cmd[1];
			*need_free = 0;
		}
	}
	else
	{
		target = cmd->full_cmd[1];
		*need_free = 0;
	}
	return (target);
}

int	builtin_cd(t_shell *cmd, t_req *req)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;
	int		arg_count;
	int		need_free;

	arg_count = 0;
	while (cmd->full_cmd[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		print_cd_error(NULL, "too many arguments");
		g_exit_status = 1;
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	target = get_cd_target(cmd, req, &need_free);
	if (!target)
	{
		if (!cmd->full_cmd[1] || (cmd->full_cmd[1][0] == '~' && !mini_getenv("HOME", req->envp, 4)))
			print_cd_error(NULL, "HOME not set");
		else
			print_cd_error(NULL, "OLDPWD not set");
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	if (chdir(target) != 0)
	{
		print_cd_error(target, strerror(errno));
		free(oldpwd);
		if (need_free)
			free(target);
		g_exit_status = 1;
		return (1);
	}
	req->envp = mini_setenv("OLDPWD", oldpwd, req->envp, 6);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup("");
	req->envp = mini_setenv("PWD", newpwd, req->envp, 3);
	free(newpwd);
	if (need_free)
		free(target);
	g_exit_status = 0;
	return (0);
}
