/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:23:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:23:08 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_shell		t_shell;
typedef struct s_request	t_req;
typedef struct s_list		t_list;

typedef struct s_pipeline_data
{
	int		input_fd;
	int		pipe_fd[2];
	int		output_fd;
	int		real_in;
	int		i;
	pid_t	*pids;
}	t_pipeline_data;

void			set_fd(int fd_from, int fd_to);
void			close_extra_fds(int keep1, int keep2);
void			restore_io(int *backup_in, int *backup_out);

void			handle_builtin_execution(t_shell *cmd, t_req *req);
void			handle_external_execution(t_shell *cmd, t_req *req);

pid_t			exec_external_cmd(t_shell *cmd, t_req *req, int in_fd,
					int out_fd);

void			exec_single_builtin(t_shell *cmd, t_req *req, int input_fd);

void			execute_cmds(t_list *cmds, t_req *req);

int				init_execution(t_list *cmds, pid_t **pids, t_req *req);
int				setup_pipe_output(t_list *node, t_shell *cmd, int *pipe_fd);
int				setup_pipe_input(t_shell *cmd, int input_fd);
void			handle_pipe_cleanup(int real_in, int input_fd, int output_fd,
					t_list *node);

int				handle_exec(t_shell *cmd, t_req *req, int *input_fd,
					pid_t *pid);
void			handle_empty_commands(t_shell *cmd, t_req *req,
					pid_t *pids, int i);
void			process_single_command(t_list *cmds, t_req *req, int input_fd);
void			wait_for_processes(pid_t *pids, int count, t_req *req);

int				apply_redirects(t_shell *cmd, t_req *req);
int				handle_heredoc(const char *delimiter, t_req *req);

#endif
