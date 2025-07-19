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

/* Parser functions */
t_token			**tokenize_input(const char *input);
t_list			*parse_tokens(t_token **tokens, t_req *req);
t_token			**process_input(char *output, t_req *res);
void			free_tokens(t_token **tokens);

#endif
