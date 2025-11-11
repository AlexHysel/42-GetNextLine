/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/11/09 12:45:58 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	stash_expand(char **stash, char *buffer, ssize_t len)
{
	char	*expanded;
	size_t	stash_len;

	stash_len = _strlen(*stash);
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
	{
		if (*buffer == '%' || *buffer == '\n')
			return (1);
		buffer++;
	}
	return (0);
}

char	*stash_extract_line(char **stash)
{
	char	*line;
	char	*ptr_stash;
	size_t	nl;

	nl = 0;
	while ((*stash)[nl] && (*stash)[nl] != '\n' && (*stash)[nl] != '%')
		nl++;
	line = _substr(*stash, 0, nl + 1);
	ptr_stash = *stash;
	*stash = _substr(*stash, nl + 1, _strlen(*stash) - nl);
	free(ptr_stash);
	return (line);
}

static char	*_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	if (substr)
	{
		substr[len--] = '\0';
		while (1)
		{
			substr[len] = s[start + len];
			if (len == 0)
				break ;
			len--;
		}
	}
	return (substr);
}
