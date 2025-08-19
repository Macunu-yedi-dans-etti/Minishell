/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/19 11:21:26 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "includes/types.h"
# include "includes/mini_error.h"
# include "includes/color.h"
# include "includes/tokenizer.h"
# include "includes/executor.h"
# include "includes/utilities.h"
# include "includes/parser.h"
# include "includes/builtin.h"
# include "includes/signals.h"
# include <readline/readline.h>
# include <readline/history.h>

char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				execute_pipeline(t_req *res);

int				handle_token_processing(int *i, t_req *req);
char			*expand_token_var(char *str, int *i, t_req *res);
#endif
