/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:35 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/06 06:52:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mini_getinput(t_req input)
{
	char	*user;
	char	*cwd;
	char	*input_str;
	char	*temp;
	char	hostname[256];
	char	*hostname_str;

	user = mini_getenv("USER", input.envp, 4);
	if (!user)
		user = ft_strdup("guest");
	if (!user)
		return (g_exit_status = 1, NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup("∅");
		g_exit_status = 1;
	}
	if (!cwd)
		return (free(user), g_exit_status = 1, NULL);
	temp = ft_strjoin(GREEN, user);
	free(user);
	if (!temp)
		return (free(cwd), g_exit_status = 1, NULL);
	input_str = ft_strjoin(temp, WHITE "@");
	free(temp);
	if (!input_str)
		return (free(cwd), g_exit_status = 1, NULL);
	if (gethostname(hostname, sizeof(hostname)) != 0)
		ft_strlcpy(hostname, "minishell", sizeof(hostname));
	hostname_str = ft_strjoin(BLUE, hostname);
	if (!hostname_str)
		return (free(cwd), free(input_str), g_exit_status = 1, NULL);
	temp = ft_strjoin(hostname_str, " ");
	free(hostname_str);
	if (!temp)
		return (free(cwd), free(input_str), g_exit_status = 1, NULL);
	hostname_str = ft_strjoin(input_str, temp);
	free(input_str);
	free(temp);
	if (!hostname_str)
		return (free(cwd), g_exit_status = 1, NULL);
	input_str = ft_strjoin(hostname_str, CYAN);
	free(hostname_str);
	if (!input_str)
		return (free(cwd), g_exit_status = 1, NULL);
	temp = ft_strjoin(input_str, cwd);
	free(cwd);
	free(input_str);
	if (!temp)
		return (g_exit_status = 1, NULL);
	input_str = ft_strjoin(temp, WHITE " $ " DEFAULT);
	free(temp);
	if (!input_str)
		return (g_exit_status = 1, NULL);
	return (input_str);
}

