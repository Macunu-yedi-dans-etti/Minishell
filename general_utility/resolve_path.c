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

char	*resolve_path(char *cmd, char **envp)
{
	char	*path_value;
	char	**paths;
	char	*full_path;
	int		i;

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
	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_double_free(&paths);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	ft_double_free(&paths);
	return (NULL);
}
