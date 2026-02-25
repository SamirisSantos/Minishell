/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:54:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/21 22:05:33 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp_cpy[i])
	{
		ft_printf(STDOUT_FILENO, "%s\n", shell->envp_cpy[i]);
		i++;
	}
	ft_printf(1, "\n");
	shell->exit_status = 0;
}
