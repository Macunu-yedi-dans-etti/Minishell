/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_fd(int fd_from, int fd_to)
{
	if (fd_from != fd_to)
	{
		dup2(fd_from, fd_to);
		close(fd_from);
	}
}

void	close_extra_fds(int keep1, int keep2)
{
	int	fd_limit;
	int	fd;

	fd_limit = 1024;
	fd = 3;
	while (fd < fd_limit)
	{
		if (fd != keep1 && fd != keep2)
			close(fd);
		fd++;
	}
}

void	restore_io(int *backup_in, int *backup_out)
{
	if (*backup_out != -1)
	{
		dup2(*backup_out, STDOUT_FILENO);
		close(*backup_out);
	}
	if (*backup_in != -1)
	{
		dup2(*backup_in, STDIN_FILENO);
		close(*backup_in);
	}
}
