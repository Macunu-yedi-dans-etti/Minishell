/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:45:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 10:57:51 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int open_redirect_file(char *filename, t_redirect_type type)
{
	int fd;

	fd = -1;
	if (!filename)
	{
		ft_putstr_fd("minishell: redirect: filename is NULL\n", 2);
		g_exit_status = 1;
		return (-1);
	}
	if (type == R_IN)
		fd = open(filename, O_RDONLY);
	else if (type == R_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == R_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exit_status = 1;
	}
	return (fd);
}

int apply_redirects(t_shell *cmd)
{
	t_redirect *redir = cmd->redirects;
	int last_in = -1, last_out = -1;
	int fd;
	int error = 0;

	// Open all redirects in order
	while (redir)
	{
		if (redir->type == R_IN)
		{
			fd = open_redirect_file(redir->filename, R_IN);
			if (fd < 0)
			{
				error = 1;
				break;
			}
			if (last_in != -1 && last_in != STDIN_FILENO)
				close(last_in);
			last_in = fd;
		}
		else if (redir->type == R_OUT)
		{
			fd = open_redirect_file(redir->filename, R_OUT);
			if (fd < 0)
			{
				error = 1;
				break;
			}
			if (last_out != -1 && last_out != STDOUT_FILENO)
				close(last_out);
			last_out = fd;
		}
		else if (redir->type == R_APPEND)
		{
			fd = open_redirect_file(redir->filename, R_APPEND);
			if (fd < 0)
			{
				error = 1;
				break;
			}
			if (last_out != -1 && last_out != STDOUT_FILENO)
				close(last_out);
			last_out = fd;
		}
		redir = redir->next;
	}
	if (error)
	{
		if (last_in != -1 && last_in != STDIN_FILENO)
			close(last_in);
		if (last_out != -1 && last_out != STDOUT_FILENO)
			close(last_out);
		return 1;
	}
	if (last_in != -1)
		cmd->infile = last_in;
	if (last_out != -1)
		cmd->outfile = last_out;
	return 0;
}
