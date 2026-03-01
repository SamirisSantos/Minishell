/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:54:24 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:51:04 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(t_shell *shell, t_tree *tree)
{
	int	status;

	status = shell->exit_status;
	if (tree && tree->cmd_args && tree->cmd_args[1])
		status = ft_atoi(tree->cmd_args[1]);
	free_shell(shell);
	ft_printf(1, "exit\n");
	exit(status);
}
