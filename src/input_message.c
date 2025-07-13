/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:35 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/13 13:36:50 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_prompt_part2(char *input_str, char *cwd)
{
	char	*temp;

	temp = ft_strjoin(input_str, CYAN);
	free(input_str);
	if (!temp)
	{
		g_exit_status = 1;
		return (free(cwd), NULL);
	}
	input_str = ft_strjoin(temp, cwd);
	free(cwd);
	free(temp);
	if (!input_str)
	{
		g_exit_status = 1;
		return (NULL);
	}
	temp = ft_strjoin(input_str, WHITE " $ " DEFAULT);
	free(input_str);
	if (!temp)
	{
		g_exit_status = 1;
		return (NULL);
	}
	return (temp);
}

static char	*build_prompt(char *user, char *cwd)
{
	char	*input_str;
	char	*temp;

	temp = ft_strjoin(GREEN, user);
	if (!temp)
	{
		g_exit_status = 1;
		return (free(cwd), NULL);
	}
	input_str = ft_strjoin(temp, WHITE "@");
	(free(temp), free(user));
	if (!input_str)
	{
		g_exit_status = 1;
		return (free(cwd), NULL);
	}
	temp = ft_strjoin(input_str, BLUE "soysal&&halusminishell ");
	free(input_str);
	if (!temp)
	{
		g_exit_status = 1;
		return (free(cwd), NULL);
	}
	input_str = temp;
	return (build_prompt_part2(input_str, cwd));
}

char	*mini_getinput(t_req input)
{
	char	*user;
	char	*cwd;

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
	return (build_prompt(user, cwd));
}
