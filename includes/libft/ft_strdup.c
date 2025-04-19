/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 08:41:56 by haloztur          #+#    #+#             */
/*   Updated: 2024/10/27 08:41:56 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *ptr)
{
	int		i;
	int		len;
	char	*cp;

	i = 0;
	len = 0;
	while (ptr[len])
		len++;
	cp = (char *)malloc ((len + 1) * sizeof(char));
	if (!cp)
		return (cp);
	while (ptr[i])
	{
		cp[i] = ptr[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
