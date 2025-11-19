/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:18:43 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/04 16:41:09 by cpinho-c         ###   ########.fr       */
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
		i++;
	}
	return (i);
}

char	**ft_realloc_envp(char **envp, size_t old_size)
{
	char	**new_envp;
	size_t	i;
	size_t	new_size;

	new_size = old_size + 1;
	new_envp = (char **)malloc((new_size + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
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
