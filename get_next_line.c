/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:34 by afomin            #+#    #+#             */
/*   Updated: 2025/12/03 15:29:02 by afomin           ###   ########.fr       */
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

static char	*_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s || !len)
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

static void	stash_expand(char **stash, char *buffer, ssize_t len)
{
	char	*expanded;
	size_t	full_len;

	full_len = _strlen(*stash) + len;
	expanded = malloc(full_len + 1);
	if (expanded)
	{
		expanded[full_len] = '\0';
		while (len)
			expanded[--full_len] = buffer[--len];
		while (full_len--)
			expanded[full_len] = (*stash)[full_len];
	}
	free(*stash);
	*stash = expanded;
}

static char	*stash_extract_line(char **stash)
{
	char	*line;
	char	*ptr_stash;
	size_t	nl;
	size_t	stash_len;

	nl = 0;
	while ((*stash)[nl] && (*stash)[nl] != '\n')
		nl++;
	stash_len = _strlen(*stash);
	line = _substr(*stash, 0, ++nl);
	ptr_stash = *stash;
	if (nl < stash_len)
		*stash = _substr(*stash, nl, stash_len - nl);
	else
		*stash = NULL;
	free(ptr_stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		was_read;

	buffer = init(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	was_read = BUFFER_SIZE;
	if (!line_end_found(stash))
	{
		while (was_read == BUFFER_SIZE && !line_end_found(buffer))
		{
			was_read = read(fd, buffer, BUFFER_SIZE);
			stash_expand(&stash, buffer, was_read);
		}
	}
	free(buffer);
	if (was_read > 0)
		return (stash_extract_line(&stash));
	if (stash)
		free(stash);
	return (NULL);
}
/*
#include <stdio.h>

int	main(int arg_count, char *args[])
{
	int		fd;
	char	*line;

	if (arg_count > 1)
		fd = open(args[1], O_RDONLY);
	else
		fd = open("get_next_line.h", O_RDONLY);

	line = get_next_line(fd);

	printf("\n===== TEST =====\nBUFFER SIZE = %d\n", BUFFER_SIZE);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("================\n\n");
}*/
