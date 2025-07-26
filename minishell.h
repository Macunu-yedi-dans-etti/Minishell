/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/26 17:10:57 by haloztur         ###   ########.fr       */
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

/* Core functions */
char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				execute_pipeline(t_token **tokens, t_req *res);
void			free_redirects(t_redirect *redir);

/* Parser utility functions */
t_shell			*init_cmd(t_req *req);
void			add_redirect(t_shell *cmd, t_redirect_type type, char *filename);
int				is_redirect(const char *token);
int				process_empty_cmd_case(t_token **tokens, int *i, t_list **cmds, t_req *req);
int				process_pipe_case(t_token **tokens, int *i, t_list **cmds, t_req *req);
int				handle_token_processing(t_shell *cmd, t_token **tokens, int *i, t_req *req);
int				set_redirection(t_shell *cmd, t_token **tokens, int *i, t_req *req);

/* Tokenizer functions */
int				is_separator(char c);
int				is_operator(char c);
t_token			*create_token(const char *str, int quote);
t_token			*create_token_and_free(char *str, int quote);
t_token			*get_operator_token(const char *input, int *i);
t_token			*get_word_token(const char *input, int *i);
t_token			**tokenize_input(const char *input);
int				resize_token_array(t_token ***tokens, int *capacity,
					int count);
int				determine_quote_type(int has_single, int has_double,
					int has_unquoted);

#endif