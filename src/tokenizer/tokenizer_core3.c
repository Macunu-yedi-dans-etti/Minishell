/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:19:52 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:19:52 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	determine_quote_type(int has_single, int has_double, int has_unquoted)
{
	if (has_unquoted || has_double)
		return (QUOTE_DOUBLE);
	else if (has_single)
		return (QUOTE_SINGLE);
	return (QUOTE_NONE);
}
