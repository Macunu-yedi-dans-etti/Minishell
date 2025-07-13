/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:45:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 13:58:32 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_redirect_file(char *filename, t_redirect_type type)
{
	int	fd;

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

static int	handle_input_redirect(t_redirect *redir, int *last_in)
{
	int	fd;

	fd = open_redirect_file(redir->filename, R_IN);
	if (fd < 0)
		return (1);
	if (*last_in != -1 && *last_in != STDIN_FILENO)
		close(*last_in);
	*last_in = fd;
	return (0);
}

static int	handle_output_redirect(t_redirect *redir, int *last_out)
{
	int	fd;

	fd = open_redirect_file(redir->filename, redir->type);
	if (fd < 0)
		return (1);
	if (*last_out != -1 && *last_out != STDOUT_FILENO)
		close(*last_out);
	*last_out = fd;
	return (0);
}

int	apply_redirects(t_shell *cmd)
{
	t_redirect	*redir;
	int			last_in;
	int			last_out;

	redir = cmd->redirects;
	last_in = -1;
	last_out = -1;
	while (redir)
	{
		if (redir->type == R_IN && handle_input_redirect(redir, &last_in))
			return (1);
		if ((redir->type == R_OUT || redir->type == R_APPEND)
			&& handle_output_redirect(redir, &last_out))
			return (1);
		redir = redir->next;
	}
	if (last_in != -1)
		cmd->infile = last_in;
	if (last_out != -1)
		cmd->outfile = last_out;
	return (0);
}
