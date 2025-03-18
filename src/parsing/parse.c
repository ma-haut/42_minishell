/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/18 15:10:22 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast_type	type;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
			return (free_ast(node), NULL);
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		if (!node)
			node = create_operator_node(type, NULL, NULL);
		else
			node = create_operator_node(type, node, NULL);
		node->file = ft_strdup((*tokens)->value);
		node->file_quoted = (*tokens)->is_quoted;
		*tokens = (*tokens)->next;
		if ((*tokens) && is_redirection(*tokens, 0))
			node->left = parse_redir(tokens, node);
		else if ((*tokens) && ((*tokens)->type == WORD))
			node->left = parse_word(tokens, node);
	}
	return (node);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	node = left;
	if ((*tokens)->type == WORD)
		node = parse_command(tokens);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (free_ast(left), NULL);
	}
	node = parse_redir(tokens, node);
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;

	left = NULL;
	if (check_error(tokens) == -1)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
			left = parse_redir(tokens, left);
		else if ((*tokens)->type == WORD)
			left = parse_word(tokens, left);
		else if ((*tokens)->type == PIPE)
			left = parse_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
		else
			return (print_errors(7), free_ast(left), NULL);
		if (!left)
			return (NULL);
	}
	return (left);
}
