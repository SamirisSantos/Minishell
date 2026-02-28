/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:17 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/21 22:02:18 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(t_shell *shell, t_tree *tree)
{
	int	i;

	i = 0;
	if (check_options(shell, tree->cmd_args))
		return ;
	if (tree->cmd_args && tree->cmd_args[1])
		ft_printf(STDOUT_FILENO, "pwd: too many arguments\n");
	else
	{
		while (shell->envp_cpy[i])
		{
			if (ft_strncmp(shell->envp_cpy[i], "PWD=", 4) == 0)
			{
				ft_printf(STDOUT_FILENO, "%s\n", shell->envp_cpy[i] + 4);
				shell->exit_status = 0;
				return ;
			}
			i++;
		}
	}
	shell->exit_status = 1;
}
