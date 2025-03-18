/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:21:41 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/18 16:03:52 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_arguments(t_token **tokens, t_ast *node)
{
	int		i;
	int		count;

	i = 0;
	count = count_args(*tokens);
    node->value = malloc(sizeof(char *) * (count + 1));
	node->value_quoted = malloc(sizeof(int) * count);
	while (*tokens && ((*tokens)->type == WORD))
	{
		node->value[i] = ft_strdup((*tokens)->value);
		if (!node->value[i])
		{
			ft_free(node->value, i);
			return ;
		}
		node->value_quoted[i] = (*tokens)->is_quoted;
		*tokens = (*tokens)->next;
		i++;
	}
	node->value[i] = NULL;
}

t_ast *word_redir(t_token **tokens, t_ast *cmd_node)
{
	t_ast	*new_redir;

	while (*tokens && is_redirection(*tokens, 0))
	{
		new_redir = parse_redir(tokens, NULL);
		if (!new_redir)
			return (free_ast(cmd_node), NULL);
		if (!new_redir->left)
			new_redir->left = cmd_node;
		else
			free_ast(cmd_node);
		cmd_node = new_redir;
	}
	return cmd_node;
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd_node = NULL;

	if (!tokens || !(*tokens))
		return (NULL);
	cmd_node = create_command_node(tokens);
	cmd_node = word_redir(tokens, cmd_node);
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
	if (!(*tokens) || ((*tokens)->type != WORD && is_redirection((*tokens),
				0) != 1))
		return (print_errors(1), free_ast(left), NULL);
	if (is_redirection((*tokens), 0))
		right = parse_redir(tokens, left);
	else if ((*tokens)->type == WORD)
		right = parse_word(tokens, NULL);
	if (!right)
		return (print_errors(2), free_ast(left), NULL);
	return (create_operator_node(type, left, right));
}
