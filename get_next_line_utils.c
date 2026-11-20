/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:16:27 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/19 14:16:29 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcheck(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*update_remainder(char *remainder)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i] || !remainder[i + 1])
		return (free(remainder), NULL);
	i++;
	new = malloc(((ft_strlen(remainder) - i) + 1) * sizeof(char));
	if (!new)
		return (free(remainder), NULL);
	j = 0;
	while (remainder[i])
		new[j++] = remainder[i++];
	new[j] = '\0';
	free(remainder);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*get_line_from_remainder(char *remainder)
{
	size_t	i;
	char	*new;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i += 1;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		new[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}
