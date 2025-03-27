/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/27 13:21:06 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input[0])
		return (1);
	while (input[i])
	{
		if ((input[i] == '!' && input[i + 1] == '!') || (input[i] == ':'
				&& input[i + 1] == ':'))
			return (0);
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '!'
			&& input[i] != ':')
			return (0);
		i++;
	}
	return (1);
}

static int	check_redir(t_token *tokens)
{
	if ((is_redirection(tokens) && !tokens->next) || (is_redirection(tokens)
			&& tokens->next->type != WORD))
	{
		ft_printf_error(2,
			"minishell: syntax error near unexpected token '%s'\n",
			get_token_type_str(tokens->type));
		return (-1);
	}
	return (0);
}

static int	check_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (is_pipe_or_logical(temp))
	{
		ft_printf_error(2,
			"minishell: syntax error near unexpected token '%s'\n",
			get_token_type_str(temp->type));
		return (-1);
	}
	while (temp)
	{
		if (is_redirection(temp) && (check_redir(temp) == -1))
			return (-1);
		if ((is_pipe_or_logical(temp) && !temp->next)
			|| (is_pipe_or_logical(temp) && is_pipe_or_logical(temp->next)))
		{
			ft_printf_error(2,
				"minishell: syntax error near unexpected token '%s'\n",
				get_token_type_str(temp->type));
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}

void	parsing(char *input, t_shell *shell)
{
	int		check;

	check = check_input(input);
	if (check == 0)
		shell->tokens = tokenize(input);
	if (shell->tokens)
	{
		if (check_tokens(shell->tokens) == 0)
		{
			shell->tokens_copy = shell->tokens;
			shell->root = parse(&shell->tokens);
		}
		else
			free_tokens(shell->tokens);
	}
	if (!shell->root && check == 0)
		g_last_exit_code = EXIT_FAILURE;
}
