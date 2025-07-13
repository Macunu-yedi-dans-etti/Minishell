/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:57 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 12:47:19 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i;
	int		len;
	char	*new_entry;

	if (n < 0)
		n = ft_strlen(var);
	new_entry = ft_strjoin(var, "=");
	new_entry = ft_strjoin_free(new_entry, value);
	i = 0;
	while (envp && envp[i])
	{
		len = ft_find_chr(envp[i], '=');
		if (len < n)
			len = n;
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (envp);
		}
		i++;
	}
	envp = ft_double_extension(envp, new_entry);
	free(new_entry);
	return (envp);
}

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
