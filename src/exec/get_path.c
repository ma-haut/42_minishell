/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:54:20 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/27 11:10:23 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*freejoin(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin((const char *) s1, (const char *) s2);
	if (temp)
		free(s1);
	return (temp);
}

static char	**find_path(char **envp)
{
	char	**paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!(*envp))
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (perror("malloc"), NULL);
	return (paths);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	paths = find_path(envp);
	if (paths)
	{
		while (paths[i] != NULL)
		{
			pathname = ft_strjoin(paths[i], "/");
			pathname = freejoin(pathname, cmd);
			if (!pathname)
				return (free_strtab(paths), perror("malloc"), NULL);
			if (access(pathname, X_OK) == 0)
				return (free_strtab(paths), pathname);
			free(pathname);
			i++;
		}
		free_strtab(paths);
	}
	return (NULL);
}
