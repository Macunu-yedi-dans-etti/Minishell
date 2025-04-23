#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "includes/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>

void	*paths(char *cmd, char **env);

void	ft_free(char **arr);

void	ft_err(char *str);

int		build_exit(char **args);

char	**copy_env(char **envp);
int		builtin_env(char **env);

# endif
