/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:49:15 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 12:53:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_path(const char *dir, const char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

static char	*try_resolve_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (NULL);
}

char	**ft_double_copy(char **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			ft_double_free(&copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*resolve_path(char *cmd, char **envp)
{
	char	*path_value;
	char	**paths;
	char	*full_path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_value = mini_getenv("PATH", envp, 4);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	free(path_value);
	if (!paths)
		return (NULL);
	full_path = try_resolve_in_paths(cmd, paths);
	ft_double_free(&paths);
	return (full_path);
}
