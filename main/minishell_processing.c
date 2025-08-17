/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:19:38 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/10 11:10:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_input(char *output, t_req *res)
{
	char	*trimmed_output;

	add_history(output);
	trimmed_output = ft_strtrim(output, " \t");
	if (!trimmed_output || !trimmed_output[0])
	{
		if (trimmed_output)
			free(trimmed_output);
		return (0);
	}
	if (ft_strncmp(trimmed_output, "\"\"", ft_strlen(trimmed_output)) == 0
		|| ft_strncmp(trimmed_output, "''", ft_strlen(trimmed_output)) == 0)
		return (ms_error(ERR_NO_CMD, trimmed_output, 127, res),
			free(trimmed_output), 0);
	res->trimmed_input = trimmed_output;
	if (!tokenize_and_validate(res))
		return (free(trimmed_output), 0);
	free(trimmed_output);
	return (1);
}

int	execute_pipeline(t_req *res)
{
	res->cmds = NULL;
	res->cur_cmd = NULL;
	parse_tokens(res);
	if (!res->cmds)
		return (0);
	execute_cmds(res);
	if (res->tokens && res->tokens[0])
		res->envp = mini_setenv("_", res->tokens[0], res->envp, 1);
	free_cmds(res->cmds);
	res->cmds = NULL;
	return (1);
}
