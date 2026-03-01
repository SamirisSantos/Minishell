/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 21:00:57 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/26 21:00:57 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	create_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->xcmd->cmd_count - 1)
	{
		if (pipe(shell->xcmd->pipe_fd[i]) == -1)
		{
			ft_printf(STDERR_FILENO, "%s", strerror(errno));
			shell->exit_status = 1;
			close_pipes(shell, i);
			return ;
		}
		i++;
	}
}

void	init_pipes(t_shell *shell)
{
	int	i;

	if (shell->xcmd->cmd_count < 2)
		return ;
	shell->xcmd->pipe_fd = (int **)ft_calloc(shell->xcmd->cmd_count - 1,
			sizeof(int *));
	if (!shell->xcmd->pipe_fd)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return ;
	}
	i = -1;
	while (++i < shell->xcmd->cmd_count - 1)
	{
		shell->xcmd->pipe_fd[i] = ft_calloc(2, sizeof(int));
		if (!shell->xcmd->pipe_fd[i])
		{
			shell->exit_status = 12;
			ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
			close_pipes(shell, i);
			return ;
		}
	}
	create_pipes(shell);
}
