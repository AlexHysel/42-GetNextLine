/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/11/06 20:04:44 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	line_end_found(char *buffer)
{
	while (*buffer)
		if (*buffer == '%' || *buffer++ == '\n')
			return (1);
	return (0);
}

size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*stash_get_line(**stash)
{
	char	*line;
	char	*div_stash;
	size_t	i;
	size_t	j;

	i = -1;
	while (stash[++i] != '\n' || stash[i] != '%')
		line[i] = stash[i];
	j = i - get_len(stash);
	div_stash = malloc(j + 1);
	while (j < i)
	{
		div_stash[j] = div_stash[i++];
	}
	return (line);
}
