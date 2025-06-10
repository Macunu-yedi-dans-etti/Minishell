#include "../../minishell.h"

int builtin_exit(char **args)
{
	int exit_code;

    exit_code = 0;
	printf("exit\n");
	if (args[1])
		exit_code = ft_atoi(args[1]);
	exit(exit_code);
}
