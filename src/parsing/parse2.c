/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 12:05:45 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_ast	*create_redir_node(t_token **tokens)
{
	t_ast_type	type;
	t_ast		*new_node;

	if ((*tokens)->next && is_redirection((*tokens)->next))
		return (NULL);
	type = get_redir_type(*tokens);
	*tokens = (*tokens)->next;
	new_node = create_operator_node(type, NULL, NULL);
	if (!new_node)
		return (NULL);
	new_node->file = ft_strdup((*tokens)->value);
	*tokens = (*tokens)->next;
	return (new_node);
}

t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast	*new_node;
	t_ast	*last;
	t_ast	*cmd;

	new_node = create_redir_node(tokens);
	if (!new_node)
		return (free_ast(node), NULL);
	if (!node)
		return (new_node);
	if (node->type == NODE_COMMAND)
	{
		new_node->left = node;
		return (new_node);
	}
	last = node;
	while (last->left && last->left->type != NODE_COMMAND)
		last = last->left;
	cmd = last->left;
	last->left = new_node;
	new_node->left = cmd;
	return (node);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	node = NULL;
	if (!tokens || !(*tokens))
		return (NULL);
	if (left)
		node = left;
	else if ((*tokens)->type == WORD)
		node = parse_command(tokens);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (free_ast(left), NULL);
	}
	if (*tokens && is_redirection(*tokens))
		node = parse_redir(tokens, node);
	return (node);
}
