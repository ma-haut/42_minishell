/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:20:23 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 13:19:01 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (perror("malloc"), NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token(t_token **head, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = NULL;
	new_token = create_token(type, value);
	if (!new_token)
		return (NULL);
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (new_token);
}

int	is_operator(char *word)
{
	if (!word)
		return (0);
	if (ft_strcmp(word, "<") == 0 || ft_strcmp(word, "<<") == 0
		|| ft_strcmp(word, ">") == 0 || ft_strcmp(word, ">>") == 0
		|| ft_strcmp(word, "|") == 0 || ft_strcmp(word, "||") == 0
		|| ft_strcmp(word, "&&") == 0)
		return (1);
	return (0);
}

int	is_pipe_or_logical(t_token *tokens)
{
	if (!tokens->value)
		return (0);
	if (ft_strcmp(tokens->value, "|") == 0 || ft_strcmp(tokens->value,
			"||") == 0 || ft_strcmp(tokens->value, "&&") == 0)
		return (1);
	return (0);
}

void	quote_switch(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && *double_quote == 0)
		*single_quote = !(*single_quote);
	else if (c == '"' && *single_quote == 0)
		*double_quote = !(*double_quote);
}
