#include "../minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	build_exit(char **args)
{
	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		if (!ft_is_numeric(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1); // çıkma ama hata ver
		}
		exit(ft_atoi(args[1]) % 256);
	}
	exit(0);
}