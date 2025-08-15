/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/15 22:59:40 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/types.h"
# include "includes/mini_error.h"
# include "includes/color.h"
# include "includes/executor.h"
# include "includes/utilities.h"
# include "includes/parser.h"
# include "includes/builtin.h"
# include "includes/signals.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				execute_pipeline(t_req *res);
void			free_redirects(t_redirect *redir);

t_cmd			*init_cmd(t_req *req);
int				is_redirect(const char *token);
int				process_empty_cmd_case(int *i, t_cmd **cmds, t_req *req);
int				process_pipe_case(int *i, t_cmd **cmds, t_req *req);
int				handle_token_processing(int *i, t_req *req);
int				set_redirection(int *i, t_req *req);

int				is_separator(char c);
int				is_operator(char c);
char			*get_operator_string(const char *input, int *i);
char			*get_word_string(const char *input, int *i);
char			**tokenize_input(const char *input);
char			**quote_control_and_expand(t_req *res);
int				resize_string_array(char ***tokens, int *capacity, int count);
char			*process_quotes_and_expand(char *str, t_req *res);
char			*expand_variable(char *str, int *i, t_req *res);
int				append_char_to_result(char **result, int *len, int *capacity,
					char c);
t_word_builder	init_word_builder(char **result, int *len, int *capacity);

#endif
