/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:54:42 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/27 10:58:58 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*expand_delim(char *s)
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
		if (s[i] == '\'' || s[i] == '"')
			single_quotes(&i, &new, s);
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
