#ifndef MINI_ERROR_H
#define MINI_ERROR_H

#include "libft/libft.h"

typedef enum e_error_type
{
    ERR_QUOTE = 1,
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
    ERR_HEREDOC             
}	t_error_type;

void	*ms_error(t_error_type type, const char *detail, int code);

#endif