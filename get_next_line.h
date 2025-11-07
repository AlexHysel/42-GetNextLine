/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:21:16 by afomin            #+#    #+#             */
/*   Updated: 2025/11/07 13:59:34 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

char	*get_next_line(int fd);
void	stash_expand(char **stash, char *buffer, ssize_t len);
char	*stash_extract_line(char **stash);
char	line_end_found(char *buffer);
size_t	_strlen(char *str);
char	*_substr(char *str, unsigned int start, size_t len);

#endif
