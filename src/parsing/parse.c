/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:50:40 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 00:19:22 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_ast	*process_command_args(t_token **tokens, t_ast *cmd_node,
		t_ast **cmd_ref)
{
	*cmd_ref = cmd_node;
	while (*tokens && (is_redirection(*tokens) || (*tokens)->type == WORD))
	{
		if (is_redirection(*tokens) && !is_redirection((*tokens)->next))
			cmd_node = parse_redir(tokens, cmd_node);
		else if ((*tokens)->type == WORD)
		{
			if ((*cmd_ref)->type == NODE_COMMAND)
				add_argument_to_command(*cmd_ref, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else
			return (NULL);
	}
	return (cmd_node);
}

static t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*temp;

	if (!right)
		return (print_errors(9), free_ast(left), NULL);
	temp = create_operator_node(NODE_PIPE, left, right);
	return (temp);
}

static t_ast	*process_pipe(t_token **tokens, t_ast *left)
{
	t_ast	*cmd_node;
	t_ast	*cmd_ref;

	if (!left || !(*tokens)->next)
		return (print_errors(8), free_ast(left), NULL);
	*tokens = (*tokens)->next;
	if ((*tokens)->type == WORD)
	{
		cmd_node = parse_command(tokens);
		cmd_node = process_command_args(tokens, cmd_node, &cmd_ref);
		return (create_pipe_node(left, cmd_node));
	}
	else if (is_redirection(*tokens))
	{
		cmd_node = parse_command(tokens);
		if (!cmd_node)
			return (print_errors(9), free_ast(left), NULL);
		cmd_node = process_command_args(tokens, cmd_node, &cmd_ref);
		return (create_pipe_node(left, cmd_node));
	}
	return (left);
}

t_ast	*process_command(t_token **tokens)
{
	t_ast	*cmd_node;
	t_ast	*cmd_ref;

	cmd_node = parse_command(tokens);
	return (process_command_args(tokens, cmd_node, &cmd_ref));
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;

	left = NULL;
	if (check_error(tokens) == -1)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == WORD || is_redirection(*tokens))
			left = process_command(tokens);
		else if ((*tokens)->type == PIPE)
			left = process_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
	}
	return (left);
}
