/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:28:32 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 19:20:28 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_arg_count(t_shell *cmd, t_req *req)
{
	int	count;

	count = 0;
	while (cmd->full_cmd[count])
		count++;
	if (count > 2)
	{
		req->exit_stat = 1;
		ms_error(ERR_NO_CMD,
			"too many arguments", 1, req);
		return (1);
	}
	return (0);
}

static int	free_and_error(char *oldpwd, char *target, int need_free,
		char *msg, t_req *req)
{
	print_cd_error(target, msg);
	free(oldpwd);
	if (need_free)
		free(target);
	req->exit_stat = 1;
	return (1);
}

static int	change_directory(t_shell *cmd, t_req *req,
		char **oldpwd, int *need_free)
{
	char	*target;

	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
		*oldpwd = ft_strdup("");
	target = get_cd_target(cmd, req, need_free);
	if (!target)
	{
		if (!cmd->full_cmd[1] || (cmd->full_cmd[1][0] == '~'
			&& !mini_getenv("HOME", req->envp, 4)))
			return (free_and_error(*oldpwd, NULL, 0, "HOME not set", req));
		return (free_and_error(*oldpwd, NULL, 0, "OLDPWD not set", req));
	}
	if (chdir(target) != 0)
		return (free_and_error(*oldpwd, target, *need_free, strerror(errno), req));
	return (0);
}

static void	update_env_after_cd(t_req *req, char *oldpwd, int need_free,
	char *target)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup("");
	req->envp = mini_setenv("OLDPWD", oldpwd, req->envp, 6);
	req->envp = mini_setenv("PWD", newpwd, req->envp, 3);
	free(newpwd);
	free(oldpwd);
	if (need_free)
		free(target);
	req->exit_stat = 0;
}

int	builtin_cd(t_shell *cmd, t_req *req)
{
	char	*oldpwd;
	int		need_free;

	if (check_arg_count(cmd, req))
		return (1);
	if (change_directory(cmd, req, &oldpwd, &need_free))
		return (1);
	update_env_after_cd(req, oldpwd, need_free,
		get_cd_target(cmd, req, &need_free));
	return (0);
}
