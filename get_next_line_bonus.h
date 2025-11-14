/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:28:13 by afomin            #+#    #+#             */
/*   Updated: 2025/11/12 12:08:40 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

char	*get_next_line(int fd);
void	stash_expand(char **stash, char *buffer, ssize_t len);
char	*stash_extract_line(char **stash);
char	line_end_found(char *buffer);

typedef struct s_fd_list_node
{
	int						fd;
	char					*stash;
	struct s_fd_list_node	*next;
}	t_fd_list;

#endif
