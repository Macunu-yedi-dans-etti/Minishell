/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 13:03:15 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

static int	is_valid_identifier_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!is_valid_identifier_char(str[0], 1))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_valid_identifier_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}
