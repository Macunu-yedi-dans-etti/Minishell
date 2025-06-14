/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:35 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/12 14:47:21 by musoysal         ###   ########.fr       */
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
	temp = ft_strjoin(user, "@soysal&&halusminishell ");
	input_str = ft_strjoin(temp, cwd);
	free(temp);
	free(user);
	free(cwd);
	temp = ft_strjoin(input_str, " $ ");
	free(input_str);
	return (temp);
}
