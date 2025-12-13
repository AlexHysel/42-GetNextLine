/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin afomin@student.42kl.edu.my          #+#  +:+        #+#       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:00:13 by afomin            #+#    #+#             */
/*   Updated: 2025/12/13 18:40:09 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(char *str)
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

static char	*stash_extract_line(t_fd_list *node)
{
	char	*line;
	char	*ptr_stash;
	size_t	nl;
	size_t	stash_len;

	if (!node->stash)
		return (NULL);
	stash_len = ft_strlen(node->stash);
	nl = 0;
	while (node->stash[nl] && node->stash[nl] != '\n')
		nl++;
	line = _substr(node->stash, 0, ++nl);
	ptr_stash = node->stash;
	if (nl < stash_len && ptr_stash[nl])
		node->stash = _substr(ptr_stash, nl, stash_len - nl);
	else
		node->stash = NULL;
	free(ptr_stash);
	return (line);
}

static void	stash_expand(char **stash, char *buffer, ssize_t len)
{
	char	*expanded;
	size_t	full_len;

	full_len = ft_strlen(*stash) + len;
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

char	*get_next_line(int fd)
{
	static t_fd_list	*list;
	t_fd_list			*node;
	char				*buffer;
	ssize_t				was_read;

	node = add_node(&list, fd);
	buffer = ft_calloc(BUFFER_SIZE, 1);
	if (!buffer)
		return (NULL);
	was_read = BUFFER_SIZE;
	if (!ft_strchr(node->stash, '\n') && !node->stash)
	{
		while (was_read == BUFFER_SIZE && !ft_strchr(buffer, '\n'))
		{
			was_read = read(fd, buffer, BUFFER_SIZE);
			stash_expand(&node->stash, buffer, was_read);
		}
	}
	free(buffer);
	if (was_read > 0)
		return (stash_extract_line(node));
	remove_node(node->fd, &list);
	return (NULL);
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int arg_count, char *args[])
{
    int         *fds;
    int         i;
    int         num_files;
    char        *line;
    int         total_exhausted = 0;
    int         lines_read = 0;

    num_files = (arg_count > 1) ? arg_count - 1 : 1;
    fds = (int *)malloc(sizeof(int) * num_files);
    if (!fds)    
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return (1);
    }
    if (arg_count == 1)
        fds[0] = 0;
    else
    {
        i = 0;
        while (i < num_files)
        {
            fds[i] = open(args[i + 1], O_RDONLY);    
            if (fds[i] < 0)
            {
                perror(args[i + 1]);
                int j = 0;
                while (j < i)
                {
                    if (fds[j] > 0)
                        close(fds[j]);
                    j++;
                }
                
                free(fds);
                return (1);
            }
            i++;
        }
    }
    printf("\n===== GNL TEST (BUFFER_SIZE = %d) =====\n", BUFFER_SIZE);
    printf("FILES OPENED: %d (FD 0 means STDIN)\n\n", num_files);
    i = 0;
    while (total_exhausted < num_files)
    {
        if (fds[i] != -1) 
        {
            line = get_next_line(fds[i]);

            if (line)
            {
                printf("[%d]: %s", fds[i], line);
                free(line);
                lines_read++;
            }
            else
            {
                if (fds[i] > 0)
                    close(fds[i]);
                fds[i] = -1; 
                total_exhausted++;
            }
        }
        i++;
        if (i >= num_files)
            i = 0;
    }
    printf("\n========================================\n");
    printf("Total Lines Read: %d\n", lines_read);
    printf("Cleanup: Freeing memory.\n");
    free(fds);
    return (0);
}*/
