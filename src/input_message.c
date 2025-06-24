/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:35 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/24 18:52:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mini_getinput(t_req input)
{
	char	*user;
	char	*cwd;
	char	*input_str;
	char	*temp;

	user = mini_getenv("USER", input.envp, 4);
	if (!user)
		user = ft_strdup("guest");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("∅");

	temp = ft_strjoin(GREEN, user);
	input_str = ft_strjoin(temp, WHITE "@");
	free(temp);
	temp = ft_strjoin(input_str, BLUE "soysal&&halusminishell ");
	free(input_str);
	input_str = temp;
	temp = ft_strjoin(input_str, CYAN);
	free(input_str);
	input_str = temp;
	temp = ft_strjoin(input_str, cwd);
	free(input_str);
	free(user);
	free(cwd);
	input_str = temp;
	temp = ft_strjoin(input_str, WHITE " $ " DEFAULT);
	free(input_str);

	return (temp);
}
