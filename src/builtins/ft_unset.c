/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:56 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/24 14:49:56 by sade-ara         ###   ########.fr       */
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

static void	unset_var(t_shell *shell, char *var)
{
	int		j;
	size_t	var_len;

	j = 0;
	var_len = ft_strlen(var);
	while (shell->envp_cpy[j])
	{
		if (ft_strncmp(shell->envp_cpy[j], var, var_len) == 0
			&& shell->envp_cpy[j][var_len] == '=')
		{
			free(shell->envp_cpy[j]);
			ft_fix_envp(shell, j);
			break ;
		}
		j++;
	}
}

void	ft_unset(t_shell *shell, char **cmd_args)
{
	int		i;
	int		j;
	size_t	var_len;

	if (!cmd_args)
	{
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd_args[i])
		unset_var(shell, cmd_args[i++]);
	shell->exit_status = 0;
}
