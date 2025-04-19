/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:28:38 by haloztur          #+#    #+#             */
/*   Updated: 2024/10/15 13:28:38 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	if (!destination && !source)
		return (destination);
	if (destination == source)
		return (destination);
	dest = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	if (src < dest && dest < src + num)
	{
		while (num--)
			dest[num] = src[num];
	}
	else
	{
		while (i < num)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}
