/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:56 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/11 11:47:57 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_fix_envp(t_shell *shell, int j)
{
	while (shell->envp_cpy[j])
	{
		shell->envp_cpy[j] = shell->envp_cpy[j + 1];
		j++;
	}
}

void	ft_unset(t_shell *shell, char **cmd_args)
{
	int		i;
	int		j;
	size_t	var_len;

	i = 1;
	while (cmd_args[i])
	{
		j = 0;
		var_len = ft_strlen(cmd_args[i]);
		while (shell->envp_cpy[j])
		{
			if (ft_strncmp(shell->envp_cpy[j], cmd_args[i], var_len) == 0 
				&& shell->envp_cpy[j][var_len] == '=')
			{
				free(shell->envp_cpy[j]);
				ft_fix_envp(shell, j);
				break ;
			}
			j++;
		}
		i++;
	}
	shell->exit_status = 0;
}
