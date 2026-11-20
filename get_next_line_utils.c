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

size_t  ft_strlen(const char *s)
{
    size_t i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strchr(const char *s, int c)
{
    size_t i;

    if(!s)
        return (NULL);
    i = 0;
    while(s[i])
    {
        if(s[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t i;
    size_t len;
    char *new;

    if(!s2)
        return (NULL);
    if(!s1)
        s1 = malloc(1);
    if(!s1)
        return (NULL);
    i = 0;
    new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if(new)
        return (NULL);
    i = 0;
    while(s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    j = 0;
    while(s2[j])
        new[i++] = s2[j++];
    new[i] = '\0';
    return (free(s1), new);
}

char *ft_strdup(const char *s)
{
    char *new;
    size_t i;

    if(!s)
        return (NULL);
    i = 0;
    new = malloc((ft_strlen(s) + 1) * sizeof(char));
    if(!new)
        return (NULL);
    while(s[i])
    {
        new[i] = s[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}