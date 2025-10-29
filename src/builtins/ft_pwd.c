/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:17 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/29 18:24:54 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(t_shell *shell, t_tree *tree)
{
	int	i;

	i = 0;
	while (shell->envp_cpy[i])
	{
		if (ft_strncmp(shell->envp_cpy[i],"PWD=", 4) == 0)
			ft_printf(tree->fd_out, "%s", shell->envp_cpy + 4);
		i++;
	}
}
