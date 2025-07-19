/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:25:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:25:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "libft/libft.h"

typedef struct s_request	t_req;

/* Environment utilities */
char			**mini_setenv(char *var, char *value, char **envp, int n);
char			*mini_getenv(char *var, char **envp, int n);
char			**mini_unsetenv(char ***envp, const char *var);
char			**mini_setenv_line(char ***envp, const char *line, t_req *req);

/* String utilities */
int				ft_find_chr(const char *s, char c);
char			**ft_double_extension(char **matrix, char *new_str);
char			**ft_double_copy(char **envp);
void			strip_newline(char *s);
char			*resolve_path(char *cmd, char **envp);

/* List utilities */
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new_node);

/* Memory utilities */
void			ft_free(char **tab);
void			ft_double_free(char ***freee);
void			free_cmds(t_list *cmds);
void			free_all(t_req *req);

#endif
