/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:16:16 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/19 14:16:18 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char *ft_strjoin(char *s1, char *s2);
size_t  ft_strlen(const char *s);
int	ft_strcheck(const char *s, int c);
char	*update_remainder(char *remainder);
char	*get_line_from_remainder(char *remainder);


#endif