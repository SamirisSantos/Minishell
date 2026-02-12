/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:41:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/10 17:59:29 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_pipe_pids(t_shell *shell)
{
	if (shell->xcmd->pipe_fd)
	{
		close_pipes(shell);
		free(shell->xcmd->pipe_fd);
	}
	if (shell->xcmd->pids)
		free(shell->xcmd->pids);
	if (shell->xcmd)
		free(shell->xcmd);
}

void free_pipe(t_shell *shell, int count)
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
