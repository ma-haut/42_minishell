/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:33:15 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 12:12:28 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	print_error(t_token *tokens)
{
	ft_printf_error(2, "minishell: invalid token '%s' in first position\n",
		tokens->value);
	return (1);
}

void	print_errors(int i)
{
	if (i == 1)
		ft_putstr_fd("minishell: missing command after logical operator\n", 2);
	if (i == 2)
		ft_putstr_fd("minishell: unclosed quotes\n", 2);
	if (i == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n", 2);
	if (i == 4)
		ft_putstr_fd("minishell: syntax error near unexpected token '<'\n", 2);
	if (i == 5)
		ft_putstr_fd("minishell: TEST syntax error near unexpected token '>>'\n",
			2);
	if (i == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token '>'\n", 2);
	if (i == 7)
		ft_putstr_fd("minishell: syntax error invalid token\n", 2);
	if (i == 8)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
}

int	check_error(t_token **tokens)
{
	if ((*tokens)->type == 1 || (*tokens)->type == 6 || (*tokens)->type == 7)
	{
		if ((*tokens)->type == 1)
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
				2);
		if ((*tokens)->type == 6)
			ft_putstr_fd("minishell: syntax error near unexpected token '&&'\n",
				2);
		if ((*tokens)->type == 7)
			ft_putstr_fd("minishell: syntax error near unexpected token '||'\n",
				2);
		return (-1);
	}
	return (1);
}
