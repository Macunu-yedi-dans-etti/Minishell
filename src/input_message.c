/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:35 by musoysal          #+#    #+#             */
/*   Updated: 2025/07/19 21:13:48 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_cwd_and_finalize(char *input_str, char *cwd, t_req *req)
{
	char	*temp;

	temp = ft_strjoin(input_str, cwd);
	free(input_str);
	free(cwd);
	if (!temp)
	{
		if (req)
			req->exit_stat = 1;
		return (NULL);
	}
	input_str = ft_strjoin(temp, WHITE " $ " DEFAULT);
	free(temp);
	if (!input_str)
	{
		if (req)
			req->exit_stat = 1;
		return (NULL);
	}
	return (input_str);
}

static char	*build_prompt_part2(char *input_str, char *cwd, t_req *req)
{
	char	*temp;

	temp = ft_strjoin(input_str, CYAN);
	free(input_str);
	if (!temp)
	{
		if (req)
			req->exit_stat = 1;
		return (free(cwd), NULL);
	}
	return (join_cwd_and_finalize(temp, cwd, req));
}

static char	*create_user_prefix(char *user, t_req *req)
{
	char	*temp;
	char	*input_str;

	temp = ft_strjoin(GREEN, user);
	if (!temp)
	{
		if (req)
			req->exit_stat = 1;
		return (NULL);
	}
	input_str = ft_strjoin(temp, WHITE "@");
	free(temp);
	free(user);
	if (!input_str)
	{
		if (req)
			req->exit_stat = 1;
		return (NULL);
	}
	return (input_str);
}

static char	*build_prompt(char *user, char *cwd, t_req *req)
{
	char	*input_str;
	char	*temp;

	input_str = create_user_prefix(user, req);
	if (!input_str)
		return (free(cwd), NULL);
	temp = ft_strjoin(input_str, BLUE "soysal&&halusminishell ");
	free(input_str);
	if (!temp)
	{
		if (req)
			req->exit_stat = 1;
		return (free(cwd), NULL);
	}
	return (build_prompt_part2(temp, cwd, req));
}

char	*mini_getinput(t_req input)
{
	char	*user;
	char	*cwd;

	user = mini_getenv("USER", input.envp, 4);
	if (!user)
		user = ft_strdup("guest");
	if (!user)
	{
		input.exit_stat = 1;
		return (NULL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup("∅");
		input.exit_stat = 1;
	}
	if (!cwd)
	{
		free(user);
		input.exit_stat = 1;
		return (NULL);
	}
	return (build_prompt(user, cwd, &input));
}
