/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:23:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/03/01 11:08:55 by cpinho-c         ###   ########.fr       */
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

bool	invalid_export(t_shell *shell, char **cmd_args, int i)
{
	char	*found;

	found = ft_strchr(cmd_args[i], '=');
	if (found && (ft_strncmp(cmd_args[i], found, 1) != 0))
		return (false);
	ft_printf(STDOUT_FILENO, "minishell: export: %s: not a valid identifier.\n",
		cmd_args[i]);
	shell->exit_status = 1;
	return (true);
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
