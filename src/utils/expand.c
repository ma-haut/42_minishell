/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:32:17 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/27 11:00:26 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_size_var(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[i]) || s[i] == '_')
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	else if (s[i] == '?')
		i++;
	else if (ft_isdigit(s[i]))
		i++;
	return (i);
}

char	*expand_var(char *name, t_shell *shell)
{
	char	*value;

	if (name[0] == '?')
		value = ft_itoa(g_last_exit_code);
	else
	{
		value = ft_getenv(shell, name);
		if (!value)
			value = ft_strdup("");
	}
	free(name);
	return (value);
}

void	handle_dollar(int *i, char **new, char *s, t_shell *shell)
{
	int		size_s;
	char	*temp;
	char	*result;

	(*i)++;
	size_s = count_size_var(s + *i);
	if (!size_s)
	{
		result = ft_strjoin_free(*new, "$");
		if (result)
			*new = result;
		return ;
	}
	temp = expand_var(ft_substr(s, *i, size_s), shell);
	if (!temp)
		return ;
	(*i) += size_s;
	result = ft_strjoin_free(*new, temp);
	if (result)
		*new = result;
	free(temp);
}

char	*handle_double(char *s, t_shell *shell)
{
	int		i;
	char	*new;
	char	*result;

	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
			handle_dollar(&i, &new, s, shell);
		else
		{
			result = ft_charjoin_free(new, s[i++]);
			if (result)
				new = result;
		}
	}
	free(s);
	return (new);
}

void	expand_node(t_ast *node, t_shell *shell)
{
	int	i;

	if (!node || !shell)
		return ;
	i = 0;
	if (node->type == NODE_COMMAND)
	{
		while (node->value[i])
		{
			node->value[i] = expand_value(node->value[i], shell);
			i++;
		}
	}
	else if (node->type >= NODE_REDIR_OUT && node->type < NODE_HEREDOC)
		node->file = expand_value(node->file, shell);
	else if (node->type == NODE_HEREDOC)
		node->file = expand_delim(node->file);
}
