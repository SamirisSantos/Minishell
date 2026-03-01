/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:18:43 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/25 11:39:32 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	ft_find_var_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++ ;
	}
	return (i);
}

char	**ft_realloc_envp(t_shell *shell, char **envp, size_t old_size)
{
	char	**new_envp;
	size_t	i;
	size_t	new_size;

	new_size = old_size + 1;
	new_envp = (char **)ft_calloc(new_size + 1, sizeof(char *));
	if (!new_envp)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_envp[i] = envp[i];
		i++;
	}
	free(envp);
	new_envp[new_size] = NULL;
	return (new_envp);
}
