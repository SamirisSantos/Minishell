/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:54:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/04 14:34:43 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp_cpy[i])
	{
		ft_printf(1, "%s", shell->envp_cpy[i]);
		i++;
	}
	shell->exit_status = 0;
}