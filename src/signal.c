/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:47:29 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/07 19:13:35 by musoysal         ###   ########.fr       */
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
		{
			g_req_ptr->exit_stat = EXIT_SIGINT;
			// Set a flag to trigger immediate cleanup
			g_req_ptr->should_exit = 1;
			// Cleanup any allocated memory when interrupted
			if (g_req_ptr->tokens)
			{
				free_string_array(g_req_ptr->tokens);
				g_req_ptr->tokens = NULL;
			}
			if (g_req_ptr->cmds)
			{
				free_cmds(g_req_ptr->cmds);
				g_req_ptr->cmds = NULL;
			}
		}
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
