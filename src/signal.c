/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:47:29 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/18 15:05:02 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define EXIT_SIGINT 130
#define EXIT_SIGQUIT 131

t_req	*get_signal_req(t_req *req)
{
	static t_req	*g_req_ptr;

	if (req)
	{
		g_req_ptr = req;
		return (g_req_ptr);
	}
	return (g_req_ptr);
}

void	handle_sigint(int sig)
{
	t_req	*req;

	if (sig == SIGINT)
	{
		req = get_signal_req(NULL);
		if (req)
			req->exit_stat = EXIT_SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	t_req	*req;

	if (sig == SIGQUIT)
	{
		req = get_signal_req(NULL);
		if (req)
			req->exit_stat = EXIT_SIGQUIT;
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	setup_signals(t_req *req)
{
	if (!req)
		return ;
	get_signal_req(req);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
