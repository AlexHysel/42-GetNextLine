/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:34 by afomin            #+#    #+#             */
/*   Updated: 2025/11/07 14:44:12 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		if (was_read < 0)
			return (NULL);
		if (was_read == 0)
			break ;
		buffer[was_read] = '\0';
		stash_expand(&stash, buffer, was_read);
	}
	return (stash_extract_line(&stash));
}

int	main(void)
{
	int		fd = open("get_next_line.h", O_RDONLY);
	int		i = 0;
	char	*line = get_next_line(fd);

	while (line)
	{
		line = get_next_line(fd);
		if (line)
			printf("%d: %s", i++, line);
	}
}
