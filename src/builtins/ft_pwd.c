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
	while (shell->envp_cpy[i])
	{
		if (ft_strncmp(shell->envp_cpy[i], "PWD=", 4) == 0)
		{
			ft_printf(tree->fd_out, "%s\n", shell->envp_cpy[i] + 4);
			shell->exit_status = 0;
			return ;
		}
		i++;
	}
	shell->exit_status = 1;
}
