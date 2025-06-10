#include "../minishell.h"

char **mini_setenv_line(char ***envp, const char *line)
{
	char *var;
	char *value;
	int   split;

	if (!line || !ft_strchr(line, '='))
		return (*envp);
	split = ft_find_chr(line, '=');
	var = ft_substr(line, 0, split);
	value = ft_strdup(line + split + 1);
	*envp = mini_setenv(var, value, *envp, -1);
	free(var);
	free(value);
	return (*envp);
}
