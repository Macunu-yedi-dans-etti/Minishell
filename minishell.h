/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:55 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:29:51 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/mini_error.h"
# include "includes/libft/libft.h"
# include "includes/color.h"
# include "includes/executor.h"
# include "includes/expander.h"
# include "includes/utilities.h"
# include "includes/parser.h"
# include "includes/builtin.h"
# include "includes/signals.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <unistd.h>

typedef struct s_request
{
	t_list		*cmds;
	char		**envp;
	pid_t		pid;
	int			exit_stat;
}				t_req;

typedef enum e_redirect_type
{
	R_IN,
	R_OUT,
	R_APPEND
}				t_redirect_type;

typedef struct s_redirect
{
	char					*filename;
	t_redirect_type			type;
	struct s_redirect		*next;
}				t_redirect;

typedef struct s_shell
{
	char		**full_cmd;
	char		*full_path;
	int			infile;
	int			outfile;
	char		*infile_path;
	char		*outfile_path;
	int			append_out;
	t_redirect	*redirects;
}				t_shell;

/* Core functions */
char			*mini_getinput(t_req input);
t_req			setup(char **av, char **env);
int				read_history_file(const char *filename);
void			append_history_file(const char *filename, const char *line);
int				execute_pipeline(t_token **tokens, t_req *res);
void			free_redirects(t_redirect *redir);

#endif