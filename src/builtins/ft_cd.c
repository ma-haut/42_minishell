/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:59:49 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/26 15:10:27 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*find_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (!home)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (home);
}

static char	*find_previous(t_shell *shell)
{
	char	*previous;

	previous = ft_getenv(shell, "OLDPWD");
	if (!previous)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	return (previous);
}

void	update_pwd(char *old_pwd, char *new_pwd, t_shell *shell)
{
	update_var(shell->env, "OLDPWD", old_pwd);
	update_var(shell->env, "PWD", new_pwd);
	free_strtab(shell->env_tab);
	shell->env_tab = list_to_tab(shell->env, shell);
	update_var(shell->exp, "OLDPWD", old_pwd);
	update_var(shell->exp, "PWD", new_pwd);
	if (old_pwd)
		free(old_pwd);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	cwd[4096];
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	path = NULL;
	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			EXIT_FAILURE);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = find_home(shell);
	else if (ft_strcmp(args[1], "-") == 0)
		path = find_previous(shell);
	else
		path = ft_strdup(args[1]);
	if (path && chdir(path) == -1)
		return (free(path), ft_printf_error(2, "minishell: cd: %s: ", args[1]),
			perror(""), EXIT_FAILURE);
	old_pwd = ft_getenv(shell, "PWD");
	new_pwd = getcwd(cwd, sizeof(cwd));
	update_pwd(old_pwd, new_pwd, shell);
	if (path)
		free(path);
	return (EXIT_SUCCESS);
}
