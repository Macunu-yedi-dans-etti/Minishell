/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_history_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ms_error(ERR_NO_DIR, "history file could not be opened", 1, NULL);
		return (-1);
	}
	close(fd);
	return (0);
}

void	append_history_file(const char *filename, const char *line)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ms_error(ERR_NO_DIR,
			"history file could not be opened for append", 1, NULL);
		return ;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
}
