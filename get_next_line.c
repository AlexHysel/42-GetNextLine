/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:34 by afomin            #+#    #+#             */
/*   Updated: 2025/11/09 13:59:06 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		was_read;

	while (1)
	{
		if (stash && line_end_found(stash))
			break ;
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read <= 0)
			return (NULL);
		buffer[was_read] = '\0';
		stash_expand(&stash, buffer, was_read);
	}
	return (stash_extract_line(&stash));
}
/*
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
