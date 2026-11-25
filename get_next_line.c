/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:15:49 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/19 14:16:04 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char **remainder)
{
	if (!remainder || !*remainder)
		return (NULL);
	free(*remainder);
	*remainder = NULL;
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
	static char	*remainder;
	ssize_t		read_byt;
	char		*new;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_byt = read_fill_remainder(fd, &remainder);
	if (read_byt < 0 || !remainder || remainder[0] == '\0')
		return (ft_free(&remainder));
	new = get_line_from_remainder(remainder);
	if (!new)
		return (ft_free(&remainder));
	remainder = update_remainder(remainder);
	return (new);
}
