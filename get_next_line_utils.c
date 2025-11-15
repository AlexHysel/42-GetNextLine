/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/11/15 14:33:37 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	line_end_found(char *buffer)
{
	if (!buffer)
		return (0);
	while (*buffer)
	{
		if (*buffer == '\n')
			return (1);
		buffer++;
	}
	return (0);
}

char	*init(size_t size)
{
	char	*result;

	result = malloc(size + 1);
	if (result)
	{
		while (size > 0)
			result[size--] = 0;
		result[0] = 0;
	}
	return (result);
}
