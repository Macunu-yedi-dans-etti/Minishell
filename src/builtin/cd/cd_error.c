/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:45:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 22:45:00 by haloztur         ###   ########.fr       */
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

int	cd_free_and_home_error(char *oldpwd, t_req *req)
{
	print_cd_error(NULL, "HOME not set");
	free(oldpwd);
	req->exit_stat = 1;
	return (1);
}

int	cd_free_and_oldpwd_error(char *oldpwd, t_req *req)
{
	print_cd_error(NULL, "OLDPWD not set");
	free(oldpwd);
	req->exit_stat = 1;
	return (1);
}

int	cd_free_and_chdir_error(char *oldpwd, char *target, int need_free,
		t_req *req)
{
	print_cd_error(target, strerror(errno));
	free(oldpwd);
	if (need_free)
		free(target);
	req->exit_stat = 1;
	return (1);
}
