/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:41:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:39:12 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_pipe_pids(t_shell *shell)
{
	int	i;

	if (shell->xcmd->pipe_fd)
	{
		i = 0;
		while (i < shell->xcmd->cmd_count - 1)
		{
			if (shell->xcmd->pipe_fd[i])
				free(shell->xcmd->pipe_fd[i]);
			i++;
		}
		free(shell->xcmd->pipe_fd);
		shell->xcmd->pipe_fd = NULL;
	}
	if (shell->xcmd->pids)
	{
		free(shell->xcmd->pids);
		shell->xcmd->pids = NULL;
	}
}

void	free_pipe(t_shell *shell, int count)
{
	int	i;

	if (!shell || !shell->xcmd || !shell->xcmd->pipe_fd || count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (shell->xcmd->pipe_fd[i])
		{
			if (shell->xcmd->pipe_fd[i][0] >= 0)
				close(shell->xcmd->pipe_fd[i][0]);
			if (shell->xcmd->pipe_fd[i][1] >= 0)
				close(shell->xcmd->pipe_fd[i][1]);
			free(shell->xcmd->pipe_fd[i]);
			shell->xcmd->pipe_fd[i] = NULL;
		}
		i++;
	}
	free(shell->xcmd->pipe_fd);
	shell->xcmd->pipe_fd = NULL;
}
