/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:40:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 01:05:18 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**mini_setenv_line(char ***envp, const char *line)
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
		g_exit_status = 1;
		return (*envp);
	}
	*envp = mini_setenv(var, value, *envp, -1);
	free(var);
	free(value);
	return (*envp);
}
