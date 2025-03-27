/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:01:27 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/26 14:55:14 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* args = tout ce qui suit la commande export et n est pas une redir */
/* shell = pointeur sur struct qui contient une copie de l'env */

static void	add_var_to_env(t_shell *shell, char *name, char *value)
{
	if (is_var(shell->env, name) && value && value[0])
	{
		update_var(shell->env, name, value);
		free_strtab(shell->env_tab);
		shell->env_tab = list_to_tab(shell->env, shell);
	}
	else if (value)
	{
		env_add_back(&shell->env, env_new(ft_strdup(name), ft_strdup(value),
				shell));
		free_strtab(shell->env_tab);
		shell->env_tab = list_to_tab(shell->env, shell);
	}
	if (is_var(shell->exp, name))
		update_var(shell->exp, name, value);
	else if (value)
		env_add_back(&shell->exp, env_new(ft_strdup(name), ft_strdup(value),
				shell));
	else
		env_add_back(&shell->exp, env_new(ft_strdup(name), NULL, shell));
	if (name)
		free(name);
	if (value)
		free(value);
	g_last_exit_code = EXIT_SUCCESS;
}

/* rule for var names : all char must be alphanum or '_'
	and 1st char can't be a digit */

static int	check_var_name(char *name, char *arg)
{
	int	i;

	i = 1;
	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		ft_printf_error(2, "minishell: export: '%s': not a valid identifier\n",
			arg);
		g_last_exit_code = EXIT_FAILURE;
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_printf_error(2, "minishell: export: '%s' ", arg);
			ft_printf_error(2, "not a valid identifier\n");
			g_last_exit_code = EXIT_FAILURE;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	free_both(char *name, char *value)
{
	free(name);
	free(value);
}

static void	set_name_value(char *str, char **name, char **value)
{
	int	i_equal;
	int	len;

	len = ft_strlen(str);
	i_equal = find_char(str, '=');
	if (i_equal > 0)
		*name = ft_strndup(str, i_equal);
	else
		*name = ft_strdup("");
	if (i_equal < len - 1)
		*value = ft_strdup(str + i_equal + 1);
	else
		*value = ft_strdup("");
}

int	ft_export(char **args, t_shell *shell)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	name = NULL;
	value = NULL;
	if (!args[1])
		print_exp(shell->exp);
	while (args[i])
	{
		if (find_char(args[i], '=') != -1)
		{
			set_name_value(args[i], &name, &value);
			if (check_var_name(name, args[i]))
				add_var_to_env(shell, name, value);
			else
				free_both(name, value);
		}
		else if (check_var_name(args[i], args[i]))
			add_var_to_env(shell, ft_strdup(args[i]), NULL);
		i++;
	}
	return (g_last_exit_code);
}
