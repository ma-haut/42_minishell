/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:46:57 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 11:50:12 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"

char	*ft_free_buff(char *buffer, char *buf);
char	*ft_next(char *buff);
char	*readf(int fd, char *res);
size_t	ft_strplen(const char *s);
void	*ft_calloc(size_t elementCount, size_t elementSize);
void	ft_bzero(void *s, size_t n);
char	*get_next_line(int fd);
char	*get_next_line_no_nl(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

#endif
