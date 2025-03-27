/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:11:08 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 14:20:12 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && !is_operator(tokens->value))
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_ast	*init_args(t_ast *cmd_node, char *arg)
{
	cmd_node->value = malloc(sizeof(char *) * 2);
	if (!cmd_node->value)
		return (perror("malloc"), NULL);
	cmd_node->value[0] = ft_strdup(arg);
	cmd_node->value[1] = NULL;
	return (cmd_node);
}

static int	count_value(t_ast *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->value[i])
		i++;
	return (i);
}

t_ast	*add_argument_to_command(t_ast *cmd_node, char *arg)
{
	char	**new_args;
	int		i;

	if (!cmd_node || !arg)
		return (NULL);
	if (!cmd_node->value)
		return (init_args(cmd_node, arg));
	new_args = malloc(sizeof(char *) * (count_value(cmd_node) + 2));
	if (!new_args)
		return (perror("malloc"), NULL);
	i = 0;
	while (cmd_node->value[i])
	{
		new_args[i] = cmd_node->value[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (free(new_args), NULL);
	new_args[i + 1] = NULL;
	free(cmd_node->value);
	cmd_node->value = new_args;
	return (cmd_node);
}
