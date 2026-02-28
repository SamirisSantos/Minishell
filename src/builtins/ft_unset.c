/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:56 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/28 17:49:41 by cpinho-c         ###   ########.fr       */
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

	if (!cmd_args)
	{
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	if (check_options(shell, cmd_args))
		return ;
	if (!cmd_args[1])
	{
		ft_printf(STDOUT_FILENO, "unset: not enough arguments\n");
		shell->exit_status = 1;
		return ;
	}
	while (cmd_args[i])
		unset_var(shell, cmd_args[i++]);
	shell->exit_status = 0;
}
