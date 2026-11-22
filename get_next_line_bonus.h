/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouarg <aybouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 11:25:24 by aybouarg          #+#    #+#             */
/*   Updated: 2026/11/22 11:25:27 by aybouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_strcheck(const char *s, int c);
char	*update_remainder(char *remainder);
char	*ft_strjoin(char *s1, char *s2);
char	*get_line_from_remainder(char *remainder);
void	*ft_free(char **remainder);
ssize_t	read_fill_remainder(int fd, char **remainder, char *buffer);
char	*get_next_line(int fd);

#endif
