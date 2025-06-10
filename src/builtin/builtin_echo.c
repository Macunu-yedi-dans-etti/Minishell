#include "../../minishell.h"

int	builtin_echo(t_shell *cmd)
{
	int	i;
	int	newline;

    i = 1;
    newline = 1;
	if (cmd->full_cmd[1] && !ft_strncmp(cmd->full_cmd[1], "-n", 3))
	{
		newline = 0;
		i++;
	}
	while (cmd->full_cmd[i])
	{
		ft_putstr_fd(cmd->full_cmd[i], STDOUT_FILENO);
		if (cmd->full_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
