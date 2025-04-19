#include "../minishell.h"


void	ft_err(char *str)
{
	if (!str)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(str, 2);
		exit(127);
	}
}
