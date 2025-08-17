/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:25:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:16:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "types.h"

/* Environment utilities */
char			**mini_setenv(char *var, char *value, char **envp, int n);
char			*mini_getenv(char *var, char **envp, int n);
char			**mini_unsetenv(char ***envp, const char *var);
char			**mini_setenv_line(char ***envp, const char *line, t_req *req);

/* String utilities */
int				ft_find_chr(const char *s, char c);
char			**ft_double_extension(char **matrix, char *new_str);
char			**ft_double_copy(char **envp);
char			*resolve_path(char *cmd, char **envp);

/* Memory utilities */
void			ft_double_free(char ***freee);
void			free_cmds(t_cmd *cmds);
void			free_all(t_pipeline_data *data);
void			free_req(t_req *req);
void			free_cmd(t_cmd *cmd);
void			free_redirects(t_redirect *redir);

#endif
