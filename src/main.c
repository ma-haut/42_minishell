/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:22 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 12:03:48 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_last_exit_code;

static int	interactive_mode(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			parsing(input, shell);
			if (shell->root)
				execute_ast(shell->root, shell);
		}
		else
			return (kill(-1, 0), clear_all(shell), ft_printf("exit\n"),
				exit(g_last_exit_code), 0);
		add_history(input);
		free(input);
		reset_shell(shell);
	}
}

static int	non_interactive_mode(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = get_next_line_no_nl(STDIN_FILENO);
		if (input)
		{
			parsing(input, shell);
			if (shell->root)
				execute_ast(shell->root, shell);
		}
		else
			return (kill(-1, 0), clear_all(shell), ft_printf("exit\n"),
				exit(g_last_exit_code), 0);
		free(input);
		reset_shell(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1 || !av[0])
		return (1);
	initialize_shell(&shell, envp);
	if (isatty(STDIN_FILENO))
		return (interactive_mode(&shell));
	else
		return (non_interactive_mode(&shell));
	return (0);
}
