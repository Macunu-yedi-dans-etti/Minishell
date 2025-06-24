/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:45:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/24 21:51:16 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_redirect_file(char *filename, t_redirect_type type)
{
	int	fd;

	fd = -1;
	if (!filename)
		return (-1);
	if (type == R_IN)
		fd = open(filename, O_RDONLY);
	else if (type == R_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == R_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(filename);
	return (fd);
}

int	apply_redirects(t_shell *cmd)
{
	int	mode;

	if (cmd->infile_path)
	{
		cmd->infile = open_redirect_file(cmd->infile_path, R_IN);
		if (cmd->infile < 0)
			return (1);
	}
	if (cmd->outfile_path)
	{
		if (cmd->append_out)
			mode = R_APPEND;
		else
			mode = R_OUT;
		cmd->outfile = open_redirect_file(cmd->outfile_path, mode);
		if (cmd->outfile < 0)
			return (1);
	}
	return (0);
}