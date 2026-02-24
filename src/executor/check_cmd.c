/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:58:29 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/20 16:58:29 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	cmd_not_found(t_shell *shell, t_tree *tree)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->data, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	shell->exit_status = 127;
}

static void	cmd_is_dir(t_shell *shell, t_tree *tree)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->data, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	shell->exit_status = 126;
}

int	check_cmd(t_shell *shell, t_tree *tree, int i)
{
	struct stat	sb;

	if (!shell->xcmd->cmd_path[i])
	{
		cmd_not_found(shell, tree);
		return (127);
	}
	if (stat(shell->xcmd->cmd_path[i], &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		cmd_is_dir(shell, tree);
		return (126);
	}
	return (0);
}
