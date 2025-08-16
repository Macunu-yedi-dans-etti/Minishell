/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:26:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

/* Parser functions */
void			parse_tokens(t_req *req);
int				process_input(char *output, t_req *res);
int				tokenize_and_validate(t_req *res);
char			**expand_tokens(char **tokens, t_req *res);
t_cmd			*init_cmd(void);
int				is_redirect(const char *token);
void			cleanup_and_return(t_req *req);
void			add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
int				parse_syntax_check(t_req *req);


#endif
