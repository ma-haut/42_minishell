/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:48:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 14:11:27 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*create_command_node(t_token **tokens, t_ast *node)
{
	node = malloc(sizeof(t_ast));
	if (!node)
		return (perror("malloc"), NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->file = NULL;
	node->value = NULL;
	get_arguments(tokens, node);
	return (node);
}

t_ast	*create_operator_node(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (perror("malloc"), NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->value = NULL;
	node->file = NULL;
	return (node);
}

t_ast	*init_ast(t_ast *node)
{
	node = malloc(sizeof(t_ast));
	if (!node)
		return (perror("malloc"), NULL);
	node->type = 0;
	node->value = NULL;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
