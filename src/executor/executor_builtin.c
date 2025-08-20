/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_builtin_io(t_pipeline_data *data, int *backup_in,
							int *backup_out)
{
	if (data->current_cmd->infile == STDIN_FILENO
		&& data->input_fd != STDIN_FILENO)
	{
		*backup_in = dup(STDIN_FILENO);
		dup2(data->input_fd, STDIN_FILENO);
		close(data->input_fd);
	}
	else if (data->current_cmd->infile != STDIN_FILENO)
	{
		*backup_in = dup(STDIN_FILENO);
		dup2(data->current_cmd->infile, STDIN_FILENO);
	}
	if (data->current_cmd->outfile != STDOUT_FILENO)
	{
		*backup_out = dup(STDOUT_FILENO);
		dup2(data->current_cmd->outfile, STDOUT_FILENO);
	}
}

void	exec_single_builtin(t_pipeline_data *data)
{
	int	backup_out;
	int	backup_in;

	backup_out = -1;
	backup_in = -1;
	/* Önce redirect'leri uygula: redirect-only tek komutlarda dosya oluşturulsun */
	if (apply_redirects(data))
	{
		data->req->exit_stat = 1;
		return ;
	}
	if (!data->current_cmd->full_cmd || !data->current_cmd->full_cmd[0])
	{
		/* Redirect-only builtin çağrısı: sadece IO ayarı yapıldı, çık */
		data->req->exit_stat = 0;
		return ;
	}
	setup_builtin_io(data, &backup_in, &backup_out);
	run_builtin(data);
	restore_io(&backup_in, &backup_out);
}
