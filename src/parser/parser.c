/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:14:48 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/19 18:39:33 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_tokens(t_req *req)
{
	int	i;
	int	res;

	if (parse_syntax_check(req))
		return ;
	i = 0;
	while (req->tokens[i])
	{
		if (req->heredoc_interrupted)
			return (cleanup_and_return(req));
		res = process_command_tokens(&i, req, 0);
		if (res == 1)
			return (cleanup_and_return(req));
		else if (res == 2)
		{
			if (req->heredoc_interrupted || handle_pipe_processing(&i, req))
				return (cleanup_and_return(req));
			continue ;
		}
		set_command_path(req->cur_cmd, req);
		add_cmd_to_list(&req->cmds, req->cur_cmd);
		req->cur_cmd = NULL;
		if (handle_pipe_processing(&i, req))
			return (cleanup_and_return(req));
	}
}
