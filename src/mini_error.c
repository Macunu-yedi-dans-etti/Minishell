/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:03:04 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/13 13:02:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error_message_prefix(t_error_type type)
{
	if (type == ERR_QUOTE)
		ft_putstr_fd("minishell: unmatched quote detected\n", 2);
	else if (type == ERR_DUP)
		ft_putstr_fd("minishell: duplication error\n", 2);
	else if (type == ERR_FORK)
		ft_putstr_fd("minishell: process creation failed\n", 2);
	else if (type == ERR_PIPE)
		ft_putstr_fd("minishell: pipe creation failed\n", 2);
	else if (type == ERR_PIPE_SYNTAX)
		ft_putstr_fd("minishell: syntax error near '|'\n", 2);
	else if (type == ERR_ALLOC)
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
	else if (type == ERR_NO_DIR)
		ft_putstr_fd("minishell: directory not found: ", 2);
	else if (type == ERR_NO_PERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (type == ERR_NO_CMD)
		ft_putstr_fd("minishell: unknown command: ", 2);
	else if (type == ERR_IS_DIR)
		ft_putstr_fd("minishell: is a directory: ", 2);
	else if (type == ERR_NOT_DIR)
		ft_putstr_fd("minishell: not a directory: ", 2);
	else if (type == ERR_HEREDOC)
		ft_putstr_fd("minishell: heredoc failed: ", 2);
}

static void	print_error_message_detail(const char *detail)
{
	if (detail)
	{
		ft_putstr_fd(detail, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	*ms_error(t_error_type type, const char *detail, int code)
{
	g_exit_status = code;
	print_error_message_prefix(type);
	print_error_message_detail(detail);
	return (NULL);
}
