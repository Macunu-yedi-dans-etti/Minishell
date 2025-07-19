/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:40:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 19:24:04 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**mini_setenv_line(char ***envp, const char *line, t_req *req)
{
	char	*var;
	char	*value;
	int		split;

	if (!line || !ft_strchr(line, '='))
		return (*envp);
	split = ft_find_chr(line, '=');
	var = ft_substr(line, 0, split);
	value = ft_strdup(line + split + 1);
	if (!var || !value)
	{
		free(var);
		free(value);
		if (req)
			req->exit_stat = 1;
		return (*envp);
	}
	*envp = mini_setenv(var, value, *envp, -1);
	free(var);
	free(value);
	return (*envp);
}
