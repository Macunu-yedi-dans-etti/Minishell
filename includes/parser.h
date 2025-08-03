/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:26:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:26:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

typedef struct s_token_state
{
	int				len;
	int				capacity;
}				t_token_state;

/* Parser functions */
char			**tokenize_input(const char *input);
t_list			*parse_tokens(char **tokens, t_req *req);
char			**process_input(char *output, t_req *res);
char			**tokenize_and_validate(char *trimmed_output, t_req *res);
char			**quote_control_and_expand(char **tokens, t_req *res);
int				needs_retokenization(char *str);
char			**expand_tokens(char **tokens, t_req *res);
void			free_string_array(char **tokens);
t_cmd			*init_cmd(t_req *req);
void			add_redirect(t_cmd *cmd, t_redirect_type type, char *filename);
int				is_redirect(const char *token);
void			free_redirects(t_redirect *redir);
char			*process_quotes_and_expand(char *str, t_req *res);

#endif
