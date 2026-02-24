/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:09:11 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:38:48 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	echo_no_args(t_shell *shell, t_tree *tree)
{
	if (tree->cmd_args)
		return (false);
	ft_printf(STDOUT_FILENO, "\n");
	shell->exit_status = 0;
	return (true);
}

void	ft_echo(t_shell *shell, t_tree *tree)
{
	int		i;
	bool	with_n;

	if (echo_no_args(shell, tree))
		return ;
	i = 1;
	with_n = false;
	while (tree->cmd_args[i] && is_n_flag(tree->cmd_args[i]))
	{
		i++;
		with_n = true;
	}
	while (tree->cmd_args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", tree->cmd_args[i]);
		i++;
		if (tree->cmd_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (!with_n)
		ft_printf(STDOUT_FILENO, "\n");
	shell->exit_status = 0;
}
