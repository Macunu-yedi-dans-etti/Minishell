#include "../minishell.h"

char	**remove_from_env(char **env, const char *key)
{
	int		i = 0, j = 0;
	int		key_len = ft_strlen(key);
	char	**new_env;

	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '='))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free(env);
	return (new_env);
}

int	command_unset(char ***env, char **args)
{
	int	i = 1;

	while (args[i])
	{
		*env = remove_from_env(*env, args[i]);
		i++;
	}
	return (0);
}

