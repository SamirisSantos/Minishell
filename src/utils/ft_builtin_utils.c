/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:23:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/28 17:59:14 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_print_export(t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	while (shell->envp_cpy[i])
	{
		k = 0;
		while (shell->envp_cpy[i][k] && shell->envp_cpy[i][k] != '=')
			ft_printf (1, "%c", shell->envp_cpy[i][k++]);
		if (shell->envp_cpy[i][k] == '=')
			ft_printf (1, "=\"%s\"", &shell->envp_cpy[i][k + 1]);
		ft_printf (1, "\n");
		i++;
	}
}

bool	invalid_export(t_shell *shell, char **cmd_args)
{
	if (cmd_args[1] && (ft_strncmp(cmd_args[1], "=", 1) == 0))
	{
		if (ft_strlen(cmd_args[1]) == 1)
			ft_printf(STDOUT_FILENO, "minishell: bad assignment\n");
		else
		{
			ft_printf(STDOUT_FILENO, "minishell: %s not found\n",
				cmd_args[1] + 1);
			
		}
		shell->exit_status = 1;
		return (true);
	}
	return (false);
}

bool	check_options(t_shell *shell, char **args)
{
	if (args && args[1])
	{
		if (ft_strncmp(args[1], "-", 1) == 0)
		{
			ft_printf(STDOUT_FILENO, "minishell: options not allowed\n");
			shell->exit_status = 1;
			return (true);
		}
	}
	return (false);
}
