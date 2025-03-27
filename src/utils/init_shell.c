/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:19:23 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/26 14:56:40 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	get_size_list(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

char	**list_to_tab(t_env *env, t_shell *shell)
{
	char	**copy;
	t_env	*current;
	int		i;
	char	*temp;

	if (!env)
		return (NULL);
	copy = malloc(sizeof(char *) * (get_size_list(env) + 1));
	if (!copy)
		return (perror("malloc"), NULL);
	current = env;
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->name, "=");
		if (!temp)
			return (free_strtab(copy), perror_exit("malloc", shell), NULL);
		copy[i] = ft_strjoin_free(temp, current->value);
		if (!copy[i++])
			return (free(temp), free_strtab(copy), perror_exit("malloc", shell),
				NULL);
		current = current->next;
	}
	copy[i] = NULL;
	return (copy);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	initialize_signals();
	shell->input = NULL;
	shell->tokens = NULL;
	shell->tokens_copy = NULL;
	shell->root = NULL;
	shell->env = dup_env(envp, shell);
	shell->exp = dup_env(envp, shell);
	shell->env_tab = list_to_tab(shell->env, shell);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->pipe = false;
	shell->cmd_count = 0;
}
