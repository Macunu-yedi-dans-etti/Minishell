#include "../../minishell.h"

int builtin_unset(char **args, t_req *req)
{
	int i;

    i = 1;
	while (args[i])
	{
		mini_unsetenv(&req->envp, args[i]);
		i++;
	}
	return (0);
}
