/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:12:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:25:57 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t number)
{
	size_t	sourcesize;
	size_t	i;

	sourcesize = ft_strlen(source);
	i = 0;
	if (number != 0)
	{
		while (source[i] && i < (number - 1))
		{
			destination[i] = source[i];
			i++;
		}
		destination[i] = '\0';
	}
	return (sourcesize);
}
