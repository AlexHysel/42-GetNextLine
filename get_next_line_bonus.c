/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <alexhysel@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:00:13 by afomin            #+#    #+#             */
/*   Updated: 2025/11/15 13:52:47 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*stash_extract_line(t_fd_list *node, t_fd_list *list, int was_read)
{
	char	*line;
	char	*ptr_stash;
	size_t	nl;

	if (!node->stash)
		return (NULL);
	if (was_read < 0)
	{
		remove_node(node->fd, &list);
		return (NULL);
	}
	nl = 0;
	while (node->stash[nl] && node->stash[nl] != '\n')
		nl++;
	line = _substr(node->stash, 0, nl + 1);
	ptr_stash = node->stash;
	if (was_read > 0 && ptr_stash[nl + 1])
		node->stash = _substr(ptr_stash, nl + 1, _strlen(node->stash) - nl);
	else
		node->stash = NULL;
	free(ptr_stash);
	return (line);
}

static void	stash_expand(char **stash, char *buffer, ssize_t len)
{
	char	*expanded;
	size_t	stash_len;

	stash_len = _strlen(*stash);
	expanded = malloc(stash_len + len + 1);
	if (expanded)
	{
		expanded[stash_len + len] = '\0';
		while (len--)
			expanded[stash_len + len] = buffer[len];
		while (stash_len--)
			expanded[stash_len] = (*stash)[stash_len];
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
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!line_end_found(node->stash))
	{
		while (!node->stash || !line_end_found(buffer))
		{
			was_read = read(fd, buffer, BUFFER_SIZE);
			if (was_read <= 0)
			{
				free(buffer);
				return (stash_extract_line(node, list, was_read));
			}
			buffer[was_read] = '\0';
			stash_expand(&node->stash, buffer, was_read);
		}
	}
	free(buffer);
	return (stash_extract_line(node, list, 1));
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
