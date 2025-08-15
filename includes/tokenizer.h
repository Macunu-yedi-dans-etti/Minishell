/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:12:03 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/15 23:12:03 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "types.h"

int				is_separator(char c);
int				is_operator(char c);
int				append_char_to_result(char **result, int *len, int *capacity, char c);
char			**tokenize_input(const char *input);
int				resize_string_array(char ***tokens, int *capacity, int count);
char			*get_operator_string(const char *input, int *i);
char			*get_word_string(const char *input, int *i);
char			*process_quotes_and_expand(char *input, t_req *res);
int				check_valid_tokens(char **tokens);
int				validate_quotes(char *str);
char			*process_quotes_and_expand(char *input, t_req *res);
t_word_builder	init_word_builder(char **result, int *len, int *capacity);
#endif
