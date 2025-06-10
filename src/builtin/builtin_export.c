#include "../../minishell.h"

int builtin_export(char **args, t_req *req)
{
    char *equal;
    int        i;

    i = 1;
	if (!args[1])
		return (builtin_env(req->envp));
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
            mini_setenv_line(&req->envp, args[i]);
		else
			printf("export: `%s`: not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}
