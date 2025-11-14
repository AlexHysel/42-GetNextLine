/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:34 by afomin            #+#    #+#             */
/*   Updated: 2025/11/14 15:40:33 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		was_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!line_end_found(stash))
	{
		while (!stash || !line_end_found(buffer))
		{
			was_read = read(fd, buffer, BUFFER_SIZE);
			if (was_read <= 0)
			{
				free(buffer);
				return (stash_extract_line(&stash, was_read));
			}
			buffer[was_read] = '\0';
			stash_expand(&stash, buffer, was_read);
		}
	}
	free(buffer);
	return (stash_extract_line(&stash, 1));
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
		line = get_next_line(fd);
	}
	printf("================\n\n");
}*/
