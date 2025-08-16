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
int				add_redirect(t_cmd *cmd, t_redirect_type type, char *filename);
int				is_redirect(const char *token);
void			free_redirects(t_redirect *redir);

#endif
