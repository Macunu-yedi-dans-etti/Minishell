/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:20:54 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:20:56 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ERROR_H
# define MINI_ERROR_H

# include "types.h"

typedef enum e_error_type
{
	ERR_QUOTE,
	ERR_NO_DIR,
	ERR_NO_PERM,
	ERR_NO_CMD,
	ERR_DUP,
	ERR_FORK,
	ERR_PIPE,
	ERR_PIPE_SYNTAX,
	ERR_ALLOC,
	ERR_IS_DIR,
	ERR_NOT_DIR,
	ERR_HEREDOC,
	ERR_EMPTY
}	t_error_type;

void	*ms_error(t_error_type type, const char *detail, int code, t_req *req);

#endif