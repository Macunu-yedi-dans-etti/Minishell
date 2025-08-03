/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/03 15:34:09 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/types.h"
# include "includes/mini_error.h"
# include "includes/color.h"
# include "includes/executor.h"
# include "includes/expander.h"
# include "includes/utilities.h"
# include "includes/parser.h"
# include "includes/builtin.h"
# include "includes/signals.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				execute_pipeline(char **tokens, t_req *res);
void			free_redirects(t_redirect *redir);

t_cmd			*init_cmd(t_req *req);
void			add_redirect(t_cmd *cmd, t_redirect_type type, char *filename);
int				is_redirect(const char *token);
int				process_empty_cmd_case(char **tokens, int *i, t_list **cmds, t_req *req);
int				process_pipe_case(char **tokens, int *i, t_list **cmds, t_req *req);
int				handle_token_processing(t_cmd *cmd, char **tokens, int *i, t_req *req);
int				set_redirection(t_cmd *cmd, char **tokens, int *i, t_req *req);

int				is_separator(char c);
int				is_operator(char c);
char			*get_operator_string(const char *input, int *i);
char			*get_word_string(const char *input, int *i);
char			**tokenize_input(const char *input);
char			**tokenize_and_validate(char *trimmed_output, t_req *res);
char			**quote_control_and_expand(char **tokens, t_req *res);
int				resize_string_array(char ***tokens, int *capacity, int count);
void			free_string_array(char **array);
int				has_quotes_or_variables(char *str);
char			*process_quotes_and_expand(char *str, t_req *res);
char			*expand_variable(char *str, int *i, t_req *res);
int				check_valid_tokens(char **tokens);

#endif
