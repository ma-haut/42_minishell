/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:21:41 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 14:10:12 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_arguments(t_token **tokens, t_ast *node)
{
	int	count;
	int	i;

	i = 0;
	count = count_args(*tokens);
	if (count == 0)
		return ;
	node->value = malloc(sizeof(char *) * (count + 1));
	if (!node->value)
		return (perror("malloc"));
	while (*tokens && (*tokens)->type == WORD && i < count)
	{
		node->value[i] = ft_strdup((*tokens)->value);
		if (!node->value[i])
		{
			ft_free(node->value, i);
			return ;
		}
		*tokens = (*tokens)->next;
		i++;
	}
	node->value[i] = NULL;
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd_node;

	cmd_node = NULL;
	if (!tokens || !(*tokens))
		return (NULL);
	cmd_node = create_command_node(tokens, cmd_node);
	if (!cmd_node)
	{
		return (NULL);
	}
	return (cmd_node);
}

t_ast	*parse_logical_operator(t_token **tokens, t_ast *left)
{
	t_ast		*right;
	t_ast_type	type;

	right = NULL;
	if ((*tokens)->type == AND)
		type = NODE_AND;
	else if ((*tokens)->type == OR)
		type = NODE_OR;
	else
		return (NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != WORD && is_redirection(*tokens) != 1))
		return (print_errors(1), free_ast(left), NULL);
	if (is_redirection(*tokens))
		right = process_command(tokens);
	else if ((*tokens)->type == WORD)
		right = parse_word(tokens, NULL);
	if (!right)
		return (free_ast(left), NULL);
	return (create_operator_node(type, left, right));
}
