/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/26 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <errno.h>

typedef enum e_redirect_type
{
	R_IN,
	R_OUT,
	R_APPEND
}				t_redirect_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}				t_quote_type;

typedef struct s_request
{
	t_list		*cmds;
	char		**envp;
	char		**export_list;
	pid_t		pid;
	int			exit_stat;
	int			should_exit;
}				t_req;

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

typedef struct s_token
{
	char			*str;
	t_quote_type	quote;
}				t_token;

#endif
