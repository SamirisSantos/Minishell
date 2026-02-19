/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:09:11 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/18 21:49:19 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_echo(t_shell *shell, t_tree *tree)
{
	int		i;
	bool	with_n;

	i = 1;
	with_n = false;
	while (tree->cmd_args[i] && (ft_strncmp(tree->cmd_args[i], "-n", 2) == 0)
		&& (ft_strlen(tree->cmd_args[i]) == 2))
	{
		i++;
		with_n = true;
	}
	while (tree->cmd_args[i])
	{
		ft_printf(tree->fd_out, "%s", tree->cmd_args[i]);
		i++;
		if (tree->cmd_args[i])
			ft_printf(tree->fd_out, " ");
	}
	if (!with_n)
		ft_printf(tree->fd_out, "\n");
	shell->exit_status = 0;
}
