/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_builtin_execution(t_pipeline_data *data)
{
	int				devnull;

	devnull = open("/dev/null", O_RDONLY);
	if (devnull != -1)
	{
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	data->input_fd = STDIN_FILENO;
	run_builtin(data);
	free_all(data);
	exit(data->req->exit_stat);
}
