/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:00:13 by afomin            #+#    #+#             */
/*   Updated: 2025/11/10 13:54:19 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//#include <stdio.h>

static t_fd_list	*node_by_fd(t_fd_list *list, int fd)
{
	while (list && list->fd != fd)
		list = list->next;
	return (list);
}

static void	remove_node(int fd, t_fd_list **list)
{
	t_fd_list	*prev_n;
	t_fd_list	*curr_n;

	if (*list)
	{
		curr_n = *list;
		prev_n = NULL;
		while (curr_n)
		{
			if (curr_n->fd == fd)
			{
				if (prev_n)
					prev_n->next = curr_n->next;
				else
					*list = curr_n->next;
				free(curr_n->stash);
				free(curr_n);
				return ;
			}
			prev_n = curr_n;
			curr_n = curr_n->next;
		}
	}
}

static t_fd_list	*add_node(t_fd_list **list, int fd)
{
	t_fd_list	*node;

	node = node_by_fd(*list, fd);
	if (node)
		return (node);
	node = malloc(sizeof(t_fd_list));
	if (node)
	{
		node->fd = fd;
		node->stash = NULL;
		node->next = NULL;
		if (*list)
		{
			while ((*list)->next)
				list = &((*list)->next);
			(*list)->next = node;
		}
		else
			*list = node;
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*list;
	t_fd_list			*node;
	char				buffer[BUFFER_SIZE + 1];
	ssize_t				was_read;

	node = add_node(&list, fd);
	while (1)
	{
		if (node->stash && line_end_found(node->stash))
			break ;
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read <= 0)
		{
			remove_node(fd, &list);
			return (NULL);
		}
		buffer[was_read] = '\0';
		stash_expand(&node->stash, buffer, was_read);
	}
	return (stash_extract_line(&node->stash));
}
/*
int main(int arg_count, char *args[])
{
    int         *fds;
    int         i;
    int         num_files;
    char        *line;
    int         total_exhausted = 0;

    num_files = (arg_count > 1) ? arg_count - 1 : 1;
    
    fds = (int *)malloc(sizeof(int) * num_files);
    if (!fds) 
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return (1);
    }

    if (arg_count == 1)
    {
        fds[0] = open("test_default_file.txt", O_RDONLY | O_CREAT, 0644);
        if (fds[0] < 0)
        {
            perror("Error opening default file");
            free(fds);
            return (1);
        }
    }
    else
    {
        i = 0;
        while (i < num_files)
        {
            fds[i] = open(args[i + 1], O_RDONLY); 
            if (fds[i] < 0)
            {
                perror(args[i + 1]);
                while (i > 0)
                    close(fds[--i]);
                free(fds);
                return (1);
            }
            i++;
        }
    }
    
    printf("\n===== GNL MULTI-FILE TEST =====\n");
    printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
    printf("FILES OPENED: %d\n\n", num_files);

    i = 0;
    int lines_read = 0;
    while (total_exhausted < num_files)
    {
        line = get_next_line(fds[i]);
        
        if (line)
        {
            printf("[FD %d]: %s", fds[i], line);
            free(line);
            lines_read++;
        }
        else if (fds[i] != -1) 
        {
            fds[i] = -1;
            total_exhausted++;
        }
        i++;
        if (i >= num_files)
            i = 0;
    }
    
    printf("\n================================\n");
    printf("Total Lines Read: %d\n", lines_read);
    printf("Cleanup: Closing files and freeing memory.\n");
    
    i = 0;
    while (i < num_files)
    {
        if (fds[i] > 0)
            close(fds[i]);
        i++;
    }
    free(fds);
    
    return (0);
}*/
