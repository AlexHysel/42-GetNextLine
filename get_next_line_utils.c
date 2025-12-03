/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin afomin@student.42kl.edu.my          #+#  +:+        #+#       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/12/03 15:52:00 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, int symbol)
{
	if (str)
	{
		while (*str)
		{
			if (*str == symbol)
				return (str);
			str++;
		}
		if (!symbol)
			return (str);
	}
	return (NULL);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;
	size_t	i;

	if (num && size > (size_t)-1 / num)
		return (NULL);
	i = size * num;
	array = malloc(i);
	if (array)
		while (i-- > 0)
			array[i] = 0;
	return (array);
}
