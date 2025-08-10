/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:23:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

typedef struct s_pipeline_data
{
	int		input_fd;
	int		pipe_fd[2];
	int		output_fd;
	int		real_in;
	int		i;
	int		count;
	pid_t	*pids;
	t_req	*req;
	t_cmd	*current_cmd;
}	t_pipeline_data;

void			set_fd(int fd_from, int fd_to);
void			close_extra_fds(int keep1, int keep2);
void			restore_io(int *backup_in, int *backup_out);

void			handle_builtin_execution(t_pipeline_data *data);
void			handle_external_execution(t_pipeline_data *data);

pid_t			exec_external_cmd(t_pipeline_data *data);

void			exec_single_builtin(t_pipeline_data *data);

void			execute_cmds(t_req *req);

int				init_execution(t_cmd *cmds, pid_t **pids, t_req *req);
int				setup_pipe_output(t_pipeline_data *data);
int				setup_pipe_input(t_pipeline_data *data);
void			handle_pipe_cleanup(t_pipeline_data *data);

void			handle_empty_commands(t_pipeline_data *data);
void			process_single_command(t_pipeline_data *data);
void			wait_for_processes(t_pipeline_data *data);

int				apply_redirects(t_pipeline_data *data);
int				handle_heredoc(const char *delimiter, t_req *req);

#endif
