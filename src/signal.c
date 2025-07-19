/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:47:29 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 21:23:16 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_req	*g_req_ptr = NULL;

#define EXIT_SIGINT 130
#define EXIT_SIGQUIT 131

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_req_ptr)
			g_req_ptr->exit_stat = EXIT_SIGINT;
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
		if (g_req_ptr)
			g_req_ptr->exit_stat = EXIT_SIGQUIT;
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_req(t_req *req)
{
	g_req_ptr = req;
}
