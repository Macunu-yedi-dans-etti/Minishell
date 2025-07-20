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

# include "libft/libft.h"

typedef struct s_request	t_req;
typedef enum e_redirect_type	t_redirect_type;
typedef struct s_redirect	t_redirect;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}				t_quote_type;

typedef struct s_token
{
	char			*str;
	t_quote_type	quote;
}				t_token;

typedef struct s_token_state
{
	int				len;
	int				capacity;
}				t_token_state;

/* Parser functions */
t_token			**tokenize_input(const char *input);
t_list			*parse_tokens(t_token **tokens, t_req *req);
t_token			**process_input(char *output, t_req *res);
t_token			**tokenize_and_validate(char *trimmed_output, t_req *res);
int				needs_retokenization(char *str);
int				check_valid_tokens(t_token **tokens);
t_token			**expand_tokens(t_token **tokens, t_req *res);
void			free_tokens(t_token **tokens);
t_shell			*init_cmd(t_req *req);
void			add_redirect(t_shell *cmd, t_redirect_type type, char *filename);
int				is_redirect(const char *token);
void			free_redirects(t_redirect *redir);

#endif
