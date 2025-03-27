/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_no_nl.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:50:50 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/25 11:51:27 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_line_to_display(char *buff)
{
	char	*l;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	l = ft_calloc(i + 1, sizeof(char));
	if (!l)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		l[i] = buff[i];
		i++;
	}
	l[i] = '\0';
	return (l);
}

char	*get_next_line_no_nl(int fd)
{
	char		*out;
	static char	*str[1024];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	str[fd] = readf(fd, str[fd]);
	if (!str[fd] || str[fd] == NULL)
		return (NULL);
	out = ft_line_to_display(str[fd]);
	str[fd] = ft_next(str[fd]);
	return (out);
}
