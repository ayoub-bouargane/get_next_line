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

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	new = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	*ft_free(char **remainder)
{
	if (!remainder || !*remainder)
		return (NULL);
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

ssize_t	read_fill_remainder(int fd, char **remainder, char *buffer)
{
	ssize_t	read_byt;

	read_byt = 0;
	while (!ft_strcheck(*remainder, '\n'))
	{
		read_byt = read(fd, buffer, BUFFER_SIZE);
		if (read_byt <= 0)
			break ;
		buffer[read_byt] = '\0';
		*remainder = ft_strjoin(*remainder, buffer);
		if (!*remainder)
			return (-1);
	}
	return (read_byt);
}

char	*get_next_line(int fd)
{
	static char	*remainder[FD_MAX];
	char		*buffer;
	char		*new;
	ssize_t		read_byt;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_byt = read_fill_remainder(fd, &remainder[fd], buffer);
	free(buffer);
	if (read_byt < 0 || !remainder[fd] || remainder[fd][0] == '\0')
		return (ft_free(&remainder[fd]));
	new = get_line_from_remainder(remainder[fd]);
	if (!new)
		return (ft_free(&remainder[fd]));
	remainder[fd] = update_remainder(remainder[fd]);
	return (new);
}
