/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:21:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:21:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

void			parse_tokens(t_req *req);
int				process_input(char *output, t_req *res);
int				tokenize_and_validate(t_req *res);
char			**expand_tokens(char **tokens, t_req *res);
t_cmd			*init_cmd(void);
int				is_redirect(const char *token);
void			cleanup_and_return(t_req *req);
void			add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
int				parse_syntax_check(t_req *req);
int				process_command_tokens(int *i, t_req *req);
int				handle_token_processing(int *i, t_req *req);
int				handle_pipe_processing(int *i, t_req *req);
void			set_command_path(t_cmd *cmd, t_req *req);

#endif
