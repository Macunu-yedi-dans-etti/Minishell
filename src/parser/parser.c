/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:14:48 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/20 12:40:43 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_tokens(t_req *req)
{
	int				i;
	t_parse_result	res;

	if (parse_syntax_check(req))
		return ;
	i = 0;
	while (req->tokens[i])
	{
		if (req->heredoc_interrupted)
			return (cleanup_and_return(req));
		res = process_command_tokens(&i, req, 0);
		if (res == PARSE_ERROR)
			return (cleanup_and_return(req));
		else if (res == PARSE_PIPE)
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
