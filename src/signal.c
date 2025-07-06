/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:47:29 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 06:48:32 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

#define EXIT_SIGINT 130
#define EXIT_SIGQUIT 131

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = EXIT_SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = EXIT_SIGQUIT;
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
