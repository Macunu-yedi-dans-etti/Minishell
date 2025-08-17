/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:31:01 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/17 20:34:29 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**build_new_env(char **envp, const char *var, int len)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			free(envp[i]);
		else
			new_env[j++] = envp[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**mini_unsetenv(char ***envp, const char *var)
{
	int		len;
	char	**new_env;

	if (!envp || !*envp || !var)
		return (NULL);
	len = ft_strlen(var);
	new_env = build_new_env(*envp, var, len);
	if (!new_env)
		return (NULL);
	free(*envp);
	*envp = new_env;
	return (new_env);
}

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	len;

	if (n < 0)
		n = ft_strlen(var);
	i = 0;
	while (envp && envp[i])
	{
		len = ft_find_chr(envp[i], '=');
		if (len < n)
			len = n;
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}
