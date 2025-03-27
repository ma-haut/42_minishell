/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:33:36 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/25 12:59:26 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

static void	print_change_status(char *arg, unsigned int *status)
{
	ft_printf_error(2, "minishell: exit: %s: numeric argument required\n",
		arg);
	*status = 2;
}

int	ft_exit(char **args, t_shell *shell)
{
	unsigned int	status;
	int				temp;

	status = EXIT_SUCCESS;
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (args[1] && !ft_isnum(args[1]))
		print_change_status(args[1], &status);
	else if (args[1])
	{
		temp = (unsigned char)ft_atoi(args[1]);
		if (temp >= 0 && temp <= 255)
			status = temp;
	}
	else if (!args[1])
		status = g_last_exit_code;
	clear_all(shell);
	ft_printf("exit\n");
	exit(status);
}
