/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:19:10 by haloztur          #+#    #+#             */
/*   Updated: 2024/10/12 15:19:10 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int ptr, size_t dev)
{
	size_t			i;
	unsigned char	*h;

	h = (unsigned char *) str;
	i = 0;
	while (i < dev)
	{
		h[i] = (unsigned char)ptr;
		i++;
	}
	return (str);
}
