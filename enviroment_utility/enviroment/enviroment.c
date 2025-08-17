/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:57 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/17 20:34:41 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	**update_existing_var(char *var, char *new_entry,
	char **envp, int n)
{
	int	i;
	int	len;

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
	return (NULL);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	char	*new_entry;
	char	**updated;

	if (n < 0)
		n = ft_strlen(var);
	new_entry = ft_strjoin(var, "=");
	if (!new_entry)
		return (NULL);
	new_entry = ft_strjoin_free(new_entry, value);
	if (!new_entry)
		return (NULL);
	updated = update_existing_var(var, new_entry, envp, n);
	if (updated)
		return (envp);
	envp = ft_double_extension(envp, new_entry);
	free(new_entry);
	return (envp);
}
