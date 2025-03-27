/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:46:44 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/25 14:19:42 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		i += 2;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int		i;
	bool	newline;

	if (args[1] && check_n(args[1]))
	{
		i = 2;
		newline = false;
	}
	else
	{
		i = 1;
		newline = true;
	}
	while (args[i] && args[i + 1])
		ft_printf("%s ", args[i++]);
	if (args[i] && newline == true)
		ft_printf("%s\n", args[i]);
	else if (newline == true)
		ft_printf("\n");
	else if (args[i])
		ft_printf("%s", args[i]);
	return (EXIT_SUCCESS);
}
