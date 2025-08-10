/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_and_exec(t_pipeline_data *data)
{
	close_extra_fds(data->real_in, data->output_fd);
	reset_signals();
	if (!data->current_cmd->full_cmd || !data->current_cmd->full_cmd[0] || data->current_cmd->full_cmd[0][0] == '\0')
	{
		ft_putendl_fd("minishell: empty command", 2);
		free_all(data);//5
		exit(0);
	}
	if (apply_redirects(data))
	{
		free_all(data);
		exit(1);
	}
	if (data->current_cmd->infile != STDIN_FILENO)
		set_fd(data->current_cmd->infile, STDIN_FILENO);
	else
		set_fd(data->real_in, STDIN_FILENO);
	if (data->current_cmd->outfile != STDOUT_FILENO)
		set_fd(data->current_cmd->outfile, STDOUT_FILENO);
	else
		set_fd(data->output_fd, STDOUT_FILENO);
	if (data->real_in != STDIN_FILENO)
		close(data->real_in);
	if (data->output_fd != STDOUT_FILENO)
		close(data->output_fd);
	if (is_builtin(data->current_cmd->full_cmd[0]))
		handle_builtin_execution(data);
	else
		handle_external_execution(data);
}

pid_t	exec_external_cmd(t_pipeline_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		free_all(data);//5
		return (-1);
	}
	if (pid == 0)
		setup_and_exec(data);
	return (pid);
}
