#include "../../minishell.h"

extern int g_exit_status;

static int	is_env_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

static int	get_var_len(const char *s)
{
	int i;

	i = 0;
	if (s[0] == '?')
		return (1);
	while (s[i] && is_env_char(s[i]))
		i++;
	return (i);
}

static char	*expand_var(const char *input, int *i, char **envp)
{
	int		var_len;
	char	*var_name;
	char	*value;
	char *status;

	(*i)++;
	if (input[*i] == '?')
	{
		status = ft_itoa(g_exit_status);
		(*i)++;
		return (status);
	}
	var_len = get_var_len(&input[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(input, *i, var_len);
	value = mini_getenv(var_name, envp, -1);
	free(var_name);
	(*i) += var_len;
	if (value)
		return (value);
	return (ft_strdup(""));
}

char *expand_str(const char *input, char **envp, int quote)
{
	int		i;
	int		len ;
	int		add;
	char	*expanded; 
	char	quote_flag;
	char	*result;
	char	*tmp ;

	i = 0;
	len = 1;
	quote_flag = 0;
	if (!input)
		return (NULL);

	if (quote == 1)
		return (ft_strdup(input));
	result = malloc(1);
	if (!result)
		return NULL;
	result[0] = '\0';
	while (input[i])
	{
		if (!quote_flag && (input[i] == '"' || input[i] == '\''))
		{
			quote_flag = input[i++];
			continue;
		}
		if (quote_flag && input[i] == quote_flag)
		{
			quote_flag = 0;
			i++;
			continue;
		}
		if (input[i] == '$' && quote_flag != '\'')
		{
			expanded = expand_var(input, &i, envp);
			add = ft_strlen(expanded);
			tmp = malloc(len + add);
			if (!tmp)
				return (free(result), free(expanded), NULL);
			ft_memcpy(tmp, result, len - 1);
			ft_memcpy(tmp + len - 1, expanded, add + 1);
			free(result);
			result = tmp;
			len += add;
			free(expanded);
			continue;
		}
		if (input[i] == '\\' && quote_flag == '"' &&
			(input[i + 1] == '"' || input[i + 1] == '$' || input[i + 1] == '\\'))
		{
			i++;
		}
		tmp = malloc(len + 1);
		if (!tmp)
			return (free(result), NULL);
		ft_memcpy(tmp, result, len - 1);
		tmp[len - 1] = input[i++];
		tmp[len] = '\0';
		free(result);
		result = tmp;
		len++;
	}
	return (result);
}
