/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin afomin@student.42kl.edu.my          #+#  +:+        #+#       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:21:16 by afomin            #+#    #+#             */
/*   Updated: 2025/12/03 15:42:42 by afomin           ###   ########.fr       */
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
void	*ft_calloc(size_t num, size_t size);
char	*ft_strchr(char *str, int symbol);

#endif
