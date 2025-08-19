/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:21:20 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:21:20 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

typedef enum e_redirect_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}				t_redirect_type;

typedef struct s_redirect
{
	char					*filename;
	t_redirect_type			type;
	struct s_redirect		*next;
}				t_redirect;

typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	int				infile;
	int				outfile;
	t_redirect		*redirects;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_request
{
	t_cmd		*cmds;
	t_cmd		*cur_cmd;
	char		**envp;
	char		**export_list;
	char		**tokens;
	char		*trimmed_input;
	int			exit_stat;
	int			should_exit;
	int			heredoc_interrupted;
	pid_t		pid;
}				t_req;

typedef struct s_word_builder
{
	char	**result;
	int		*len;
	int		*capacity;
}				t_word_builder;

#endif
