/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:40:55 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/25 12:52:27 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	change_fd_in(t_shell *shell, int fd)
{
	if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
		close(shell->fd_in);
	shell->fd_in = fd;
}

void	change_fd_out(t_shell *shell, int fd)
{
	if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
		close(shell->fd_out);
	shell->fd_out = fd;
}

int	check_infile(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_error(2, "minishell: %s: ", pathname);
		perror("");
	}
	return (fd);
}

int	check_outfile(char *pathname)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR, 0644);
	else
		fd = open(pathname, O_RDWR | O_TRUNC);
	if (fd == -1)
	{
		ft_printf_error(2, "minishell: %s: ", pathname);
		perror("");
	}
	return (fd);
}

int	check_outfile_app(char *pathname)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(pathname, O_RDWR | O_APPEND);
	if (fd == -1)
	{
		ft_printf_error(2, "minishell: %s: ", pathname);
		perror("");
	}
	return (fd);
}
