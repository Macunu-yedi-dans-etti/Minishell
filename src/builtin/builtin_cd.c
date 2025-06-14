/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:19:50 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:20:01 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include <errno.h>
int getOrSetExitCode(int value)
{
	static int code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}
/**
 * Environment değişkenlerinden key'e karşılık gelen değeri döndürür.
 */
char *getEnvValue(char **env, char *key)
{
	int i;
	int key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp((const char *)env[i], (const char *)key, key_len) == 0 && env[i][key_len] == '=')
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

/**
 * cd hatalarında stderr'e mesaj yazdırır ve exit_code(1) çağırır.
 */
static int printCdError(char *path, char *message)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path && *path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	getOrSetExitCode(1);
	return (1);
}

/**
 * cd komutu için hedef yolu hesaplar (~, -, ~/ gibi).
 */
char *resolveCdPath(char **env, char **args)
{
	char *path;
	char *home;
	char *joined;

	path = args[1];
	if (!path)
		return (ft_strdup(getEnvValue(env, "HOME")));
	if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = getEnvValue(env, "OLDPWD");
		if (!path)
			return (printCdError(NULL, "OLDPWD not set"), NULL);
		ft_putendl_fd(path, 1);
		return (ft_strdup(path));
	}
	if (ft_strncmp(path, "~", ft_strlen(path)) == 0)
	{
		home = getEnvValue(env, "HOME");
		if (!home)
			return (printCdError(NULL, "HOME not set"), NULL);
		return (ft_strdup(home));
	}
	if (ft_strncmp(path, "~/", 2) == 0)
	{
		home = getEnvValue(env, "HOME");
		if (!home)
			return (printCdError(NULL, "HOME not set"), NULL);
		joined = ft_strjoin(home, path + 1);
		if (!joined)
			return (printCdError(NULL, "memory allocation error"), NULL);
		return (joined);
	}
	return (ft_strdup(path));
}

/**
 * Ortam değişkenlerinde var olanı günceller, yoksa ekler.
 */
static int updateEnvVariable(char **env, char *var)
{
	int i;
	int len;
	char *key;
	char **new_env;

	key = ft_substr(var, 0, ft_strchr(var, '=') - var);
	if (!key)
		return (1);
	len = ft_strlen(key);
	i = 0;
	while ((env)[i])
	{
		if (ft_strncmp((env)[i], key, len) == 0 && (env)[i][len] == '=')
		{
			free((env)[i]);
			(env)[i] = ft_strdup(var);
			free(key);
			return (0);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (free(key), 1);
	i = -1;
	while ((env)[++i])
		new_env[i] = (env)[i];
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(env);
	env = new_env;
	free(key);
	return (0);
}

/**
 * PWD ve OLDPWD ortam değişkenlerini günceller.
 */
int updateCdEnvVariables(char **envp, char *old_pwd)
{
	char *pwd;
	char *pwd_var;
	char *oldpwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(old_pwd), printCdError(NULL, "error retrieving current directory"));
	pwd_var = ft_strjoin("PWD=", pwd);
	oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
	free(pwd);
	free(old_pwd);
	if (!pwd_var || !oldpwd_var)
		return (free(pwd_var), free(oldpwd_var), printCdError(NULL, "memory allocation error"));
	if (updateEnvVariable(envp, pwd_var) != 0 || updateEnvVariable(envp, oldpwd_var) != 0)
	{
		free(pwd_var);
		free(oldpwd_var);
		return (printCdError(NULL, "error updating environment variables"));
	}
	free(pwd_var);
	free(oldpwd_var);
	return (0);
}

/**
 * Dizin kontrolü yapar ve hata durumunda uygun mesajı döndürür.
 */
static int changeDirectory(char *path)
{
	int chdir_result;
	chdir_result = chdir(path);
	if (chdir_result != 0)
		return (printCdError(path, strerror(errno)));
	return (0);
}

/**
 * cd builtin fonksiyonu: argümanları işler, dizini değiştirir ve ortamı günceller.
 */
int	builtin_cd(char **args, char **envp)
{
	char *final_path;
	char *old_pwd;
	int argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
		return (printCdError(NULL, "too many arguments"));
	final_path = resolveCdPath(envp, args);
	if (!final_path)
		return (1);

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (free(final_path), printCdError(NULL, "error retrieving current directory"));

	if (changeDirectory(final_path) != 0)
	{
		free(old_pwd);
		return (free(final_path), printCdError(final_path, strerror(errno)));
	}

	if (updateCdEnvVariables(envp, old_pwd) != 0)
		return (free(final_path), 1);

	free(final_path);
	return (0);
}