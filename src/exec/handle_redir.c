/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:55:57 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/27 11:29:00 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	initialize_hd(t_heredoc *hd, t_ast *node, t_shell *shell)
{
	if (pipe(hd->heredoc_pipe) < 0)
		perror_exit("pipe", shell);
	hd->line_count = 1;
	hd->delim = ft_strdup(node->file);
	if (!hd->delim)
		perror_exit("malloc", shell);
	hd->delim = ft_strjoin_free(hd->delim, "\n");
	if (!hd->delim)
		perror_exit("malloc", shell);
}

static void	error_eof(int line_count, char *delim, t_heredoc *hd,
		t_shell *shell)
{
	ft_printf_error(2, "minishell: warning: here-document at line %i ",
		line_count);
	ft_printf_error(2, "delimited by end-of-file (wanted '%s')\n", delim);
	close(hd->heredoc_pipe[1]);
	close(hd->heredoc_pipe[0]);
	change_fd_in(shell, -1);
	if (hd->delim)
		free(hd->delim);
}

void	handle_heredoc(t_ast *node, t_shell *shell)
{
	t_heredoc	hd;

	initialize_hd(&hd, node, shell);
	while (1)
	{
		hd.line = get_next_line(STDIN_FILENO);
		if (!hd.line)
		{
			error_eof(hd.line_count, node->file, &hd, shell);
			return ;
		}
		if (ft_strcmp(hd.line, hd.delim) == 0)
			break ;
		ft_putstr_fd(hd.line, hd.heredoc_pipe[1]);
		free(hd.line);
		hd.line_count++;
	}
	close(hd.heredoc_pipe[1]);
	free(hd.line);
	change_fd_in(shell, hd.heredoc_pipe[0]);
	free(hd.delim);
}

int	handle_redir_node(t_ast *node, t_shell *shell)
{
	if (node->type == NODE_HEREDOC)
		handle_heredoc(node, shell);
	else if (node->type == NODE_REDIR_IN)
		change_fd_in(shell, check_infile(node->file));
	else if (node->type == NODE_REDIR_OUT)
		change_fd_out(shell, check_outfile(node->file));
	else if (node->type == NODE_APPEND)
		change_fd_out(shell, check_outfile_app(node->file));
	if (node->left && (node->left->file || (node->left->value
				&& node->left->value[0])) && shell->fd_in != -1
		&& shell->fd_out != -1)
		return (execute_ast(node->left, shell));
	else if (node->right && (node->right->file || (node->right->value
				&& node->right->value[0])) && shell->fd_in != -1
		&& shell->fd_out != -1)
		return (execute_ast(node->right, shell));
	g_last_exit_code = EXIT_FAILURE;
	return (EXIT_FAILURE);
}
