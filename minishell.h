/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 19:24:40 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "includes/types.h"
# include "includes/mini_error.h"
# include "includes/color.h"
# include "includes/tokenizer.h"
# include "includes/executor.h"
# include "includes/utilities.h"
# include "includes/parser.h"
# include "includes/builtin.h"
# include "includes/signals.h"
# include <readline/readline.h>
# include <readline/history.h>

char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				execute_pipeline(t_req *res);
void			free_redirects(t_redirect *redir);

int				is_redirect(const char *token);
int				process_empty_cmd_case(int *i, t_cmd **cmds, t_req *req);
int				process_pipe_case(int *i, t_cmd **cmds, t_req *req);
int				handle_token_processing(int *i, t_req *req);
int				set_redirection(int *i, t_req *req);


char			**quote_control_and_expand(t_req *res);

char	*expand_token_var(char *str, int *i, t_req *res);
#endif
