/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/11/06 19:09:07 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_list.h"

void	stash_expand(char **stash, char *buffer, ssize_t len)
{
	char	*expanded;
	size_t	stash_len;

	stash_len = get_len(*stash);
	expanded = malloc(stash_len + len + 1);
	if (expanded)
	{
		expanded[stash_len + len] = '\0';
		while (len--)
			expanded[stash_len + len] = buffer[len];
		while (stash_len--)
			expanded[stash_len] = (*stash)[stash_len];
	}
	free(*stash);
	*stash = expanded;
}

size_t	get_len(char *str)
{
	size_t	i

	i = 0;
	while (str[i])
		str[i++];
	return (i);
}
