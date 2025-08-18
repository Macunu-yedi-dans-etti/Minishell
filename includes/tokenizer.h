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
int				append_char_to_result(char **result, int *len, int *capacity,
					char c);
char			**tokenize_input(const char *trimmed_input, int i, int count,
					int capacity);
char			*get_word_string(const char *input, int *i);
char			*process_quotes_and_expand(char *input, t_req *res);
char			*handle_single_quotes(char *input, int *i, char *result);
#endif
