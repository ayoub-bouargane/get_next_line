/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 11:25:32 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/22 11:25:33 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_node	*get_node(t_node **head, int fd)
{
	t_node	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->rem = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

void	*remove_node(t_node **head, int fd)
{
	t_node	*curr;
	t_node	*tmp;

	curr = *head;
	tmp = NULL;
	while (curr && curr->fd != fd)
	{
		tmp = curr;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	if (!tmp)
		*head = curr->next;
	else
		tmp->next = curr->next;
	free(curr->rem);
	free(curr);
	return (NULL);
}

ssize_t	read_fill_remainder(int fd, char **remainder)
{
	ssize_t	read_byt;
	char	*buffer;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	read_byt = 0;
	while (!ft_strcheck(*remainder, '\n'))
	{
		read_byt = read(fd, buffer, BUFFER_SIZE);
		if (read_byt <= 0)
			break ;
		buffer[read_byt] = '\0';
		*remainder = ft_strjoin(*remainder, buffer);
		if (!*remainder)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return (read_byt);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*line;
	ssize_t			read_byt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&head, fd);
	if (!node)
		return (NULL);
	read_byt = read_fill_remainder(fd, &node->rem);
	if (read_byt < 0 || !node->rem || !node->rem[0])
		return (remove_node(&head, fd));
	line = get_line_from_remainder(node->rem);
	if (!line)
		return (remove_node(&head, fd));
	node->rem = update_remainder(node->rem);
	if (!node->rem)
		remove_node(&head, fd);
	return (line);
}
