/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:27:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:27:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell		t_shell;
typedef struct s_request	t_req;

/* Builtin functions */
int				run_builtin(t_shell *cmd, t_req *req);
int				is_builtin(char *cmd);
int				builtin_echo(t_shell *cmd, t_req *req);
int				builtin_pwd(t_req *req);
int				builtin_env(char **envp, t_req *req);
int				builtin_cd(t_shell *cmd, t_req *req);
int				builtin_export(char **args, t_req *req);
int				builtin_unset(char **args, t_req *req);
int				builtin_exit(char **args, t_req *req);
void			print_cd_error(char *arg, char *msg);
char			*get_cd_target(t_shell *cmd, t_req *req, int *need_free);
int				cd_free_and_home_error(char *oldpwd, t_req *req);
int				cd_free_and_oldpwd_error(char *oldpwd, t_req *req);
int				cd_free_and_chdir_error(char *oldpwd, char *target,
					int need_free, t_req *req);

#endif
