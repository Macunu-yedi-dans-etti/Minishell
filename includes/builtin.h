/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:20:32 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:20:32 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "types.h"

int				run_builtin(t_pipeline_data *data);
int				is_builtin(char *cmd);
int				builtin_echo(t_pipeline_data *data);
int				builtin_pwd(t_pipeline_data *data);
int				builtin_env(char **envp, t_req *req);
int				builtin_cd(t_pipeline_data *data);
int				builtin_export(t_pipeline_data *data);
int				builtin_unset(t_pipeline_data *data);
int				builtin_exit(t_pipeline_data *data);
char			*get_cd_target(t_cmd *cmd, t_req *req, int *need_free);
int				cd_free_and_home_error(char *oldpwd, t_req *req);
int				cd_free_and_oldpwd_error(char *oldpwd, t_req *req);
int				cd_free_and_chdir_error(char *oldpwd, char *target,
					int need_free, t_req *req);

#endif
