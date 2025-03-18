/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:33:28 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/13 13:16:28 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* args = tout ce qui suit la commande env et precede la redirection */

int	ft_env(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	print_env(shell->env);
	return (EXIT_SUCCESS);
}
