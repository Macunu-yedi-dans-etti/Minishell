#include "../minishell.h"

// envye yeni değer ekleyen fonksiyon
char	**add_to_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	// uzunluğu ölç
	i = 0;
	while(env[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);

	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var); // yeni değişkeni ekle
	new_env[i + 1] = NULL;
	//ft_free(env); // eski env'i serbest bırak
	return (new_env);
}

// export
int	command_export(char ***env, char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("export: missing argument", 2);
		return (1);
	}
	*env = add_to_env(*env, args[1]);
	return (0);
}

