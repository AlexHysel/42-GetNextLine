/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:34 by afomin            #+#    #+#             */
/*   Updated: 2025/11/06 19:36:53 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char	buffer[BUFFER_SIZE];
	ssize_t	was_read;

	while (line_end_found(buffer))
	{
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read <= 0)
			return (NULL);
		stash_expand(&stash, buffer, was_read);
	}
	return (stash);
}

int	main(void)
{
	int	fd = open("get_next_line.h", O_RDONLY);
	int	i = 0;
	char	*line = get_next_line(fd);

	while (line)
	{
		line = get_next_line(fd);  
		printf("%d: %s\n", i++, line);
	}
}
