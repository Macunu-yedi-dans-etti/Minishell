#include "../minishell.h"

int	exit_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
