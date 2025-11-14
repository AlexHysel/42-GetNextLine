/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:21:16 by afomin            #+#    #+#             */
/*   Updated: 2025/11/12 12:08:48 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

char	*get_next_line(int fd);
void	stash_expand(char **stash, char *buffer, ssize_t len);
char	*stash_extract_line(char **stash, int was_read);
char	line_end_found(char *buffer);

#endif
