/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 11:26:01 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/22 11:26:03 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	new = NULL;
	if (remainder[i] && remainder[i + 1])
		new = malloc((ft_strlen(remainder) - i) * sizeof(char));
	if (!new)
	{
		free(remainder);
		return (NULL);
	}
	i++;
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
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
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
