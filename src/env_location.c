#include "../minishell.h"

static char	*rmpaths(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, j) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

static void	free_and_print(int found, char **get_path, char **s_cmd)
{
	ft_free(get_path);
	ft_free(s_cmd);
	if (found)
		ft_putendl_fd("minishell: Permission denied", 2);
	else
		ft_putendl_fd("minishell: No such file or directory", 2);
}

static char	*check_file(char *base, char *cmd, int *found)
{
	char	*part_path;
	char	*file;

	part_path = ft_strjoin(base, "/");
	file = ft_strjoin(part_path, cmd);
	free(part_path);
	if (!access(file, F_OK))
	{
		if (!access(file, X_OK))
			return (file);
		*found = 1;
	}
	free(file);
	return (NULL);
}

void	*paths(char *cmd, char **env)
{
	char	**get_path;
	char	**s_cmd;
	char	*file;
	int		i;
	int		found;

	get_path = ft_split(rmpaths("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	i = 0;
	found = 0;
	while (get_path[i])
	{
		file = check_file(get_path[i], s_cmd[0], &found);
		if (file)
		{
			ft_free(get_path);
			ft_free(s_cmd);
			return (file);
		}
		i++;
	}
	free_and_print(found, get_path, s_cmd);
	return (NULL);
}
