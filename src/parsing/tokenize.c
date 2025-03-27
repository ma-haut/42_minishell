/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/25 14:19:57 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_word(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;
	int		single_quote;
	int		double_quote;

	start = i;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (input[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		if ((is_space(input[i]) || input[i] == '|' || input[i] == '<'
				|| input[i] == '>') && !single_quote && !double_quote)
			break ;
		i++;
	}
	word = ft_strndup(&input[start], (i - start));
	if (!word)
		perror(NULL);
	add_token(tokens, WORD, word);
	free(word);
	return (i);
}

int	process_token(char *input, int i, t_token **tokens)
{
	if (input[i] == '|')
		return (handle_pipe(input, i, tokens));
	else if (input[i] == '>')
		return (handle_redirection_out(input, i, tokens));
	else if (input[i] == '<')
		return (handle_redirection_in(input, i, tokens));
	else if (input[i] == '&' && input[i + 1] == '&')
		return (handle_and(input, i, tokens));
	else
		return (handle_word(input, i, tokens));
}

static int	has_unclosed_quotes(const char *input)
{
	int	single_quote;
	int	double_quote;
	int	i;

	if (!input)
		return (0);
	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (input[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
		return (print_errors(2), 1);
	return (0);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	if (has_unclosed_quotes(input))
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else
		{
			i = process_token(input, i, &tokens);
			if (i == -1)
				return (free_tokens(tokens), NULL);
		}
	}
	return (tokens);
}
