/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:23:13 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:23:13 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_request	t_req;

typedef struct s_process_data
{
	char	**envp;
	t_req	*req;
	int		*len;
}	t_process_data;

int				is_env_char(char c);
int				get_var_len(const char *s);
char			*append_str(char *dst, const char *src, int *len);
char			*append_char(char *dst, char c, int *len);
char			*initialize_result(void);

char			*expand_var(const char *input, int *i, char **envp, t_req *req);

char			*process_input_loop(const char *input, char **envp, t_req *req);
int				should_escape_char(const char *input, int i, int quote);

char			*expand_str(const char *input, char **envp, int quote,
					t_req *req);

#endif
