/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:11:27 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 12:35:26 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == REDIR_OUT || token->type == REDIR_IN
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

t_ast_type	get_redir_type(t_token *token)
{
	if (token->type == REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (token->type == REDIR_APPEND)
		return (NODE_APPEND);
	if (token->type == REDIR_IN)
		return (NODE_REDIR_IN);
	if (token->type == HEREDOC)
		return (NODE_HEREDOC);
	if (token->type == AND)
		return (NODE_AND);
	if (token->type == OR)
		return (NODE_OR);
	return (NODE_PIPE);
}

const char	*get_ast_type_str(t_ast_type type)
{
	if (type == NODE_PIPE)
		return ("|");
	else if (type == NODE_REDIR_IN)
		return ("<");
	else if (type == NODE_REDIR_OUT)
		return (">");
	else if (type == NODE_APPEND)
		return (">>");
	else if (type == NODE_HEREDOC)
		return ("<<");
	else if (type == NODE_AND)
		return ("&&");
	else if (type == NODE_OR)
		return ("||");
	return ("unknown");
}

const char	*get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("|");
	else if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR_APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	return ("unknown");
}
