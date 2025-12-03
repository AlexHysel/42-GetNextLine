/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomin afomin@student.42kl.edu.my          #+#  +:+        #+#       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:43:46 by afomin            #+#    #+#             */
/*   Updated: 2025/12/03 15:53:19 by afomin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char *str, int symbol)
{
	if (str)
	{
		while (*str)
		{
			if (*str == symbol)
				return ((char *)str);
			str++;
		}
		if (!symbol)
			return ((char *)str);
	}
	return (NULL);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;
	size_t	i;

	if (num && size > (size_t)-1 / num)
		return (NULL);
	i = size * num;
	array = malloc(i);
	if (array)
		while (i-- > 0)
			array[i] = 0;
	return (array);
}

t_fd_list	*node_by_fd(t_fd_list *list, int fd)
{
	while (list && list->fd != fd)
		list = list->next;
	return (list);
}

void	remove_node(int fd, t_fd_list **list)
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

t_fd_list	*add_node(t_fd_list **list, int fd)
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
