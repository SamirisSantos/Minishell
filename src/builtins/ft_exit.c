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

static bool validade_arg(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args[2])
	{
		ft_printf(STDOUT_FILENO, "minishel: exit: too many arguments\n");
		shell->exit_status = 1;
		return (false);
	}
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) == 0)
		{
			ft_printf(STDOUT_FILENO,
				"minishell: exit: %s: numeric argument required\n", args[1]);
			shell->exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}


void	ft_exit(t_shell *shell, t_tree *tree)
{
	long long int	status;

	status = shell->exit_status;
	if (tree && tree->cmd_args)
	{
		if (!validade_arg(shell, tree->cmd_args))
			return ;
		errno = 0;
		status = ft_atoll(tree->cmd_args[1]);
		if (errno == ERANGE)
		{
			ft_printf(STDOUT_FILENO,
				"minishell: exit: %s: numeric argument required\n",
				tree->cmd_args[1]);
			shell->exit_status = 1;
			return ;
		}
	}
	free_shell(shell);
	ft_printf(STDOUT_FILENO, "exit\n");
	exit((unsigned char)status);
}
