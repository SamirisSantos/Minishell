/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:36:39 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/18 22:13:23 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_pipes(t_shell *shell, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (shell->xcmd->pipe_fd[i])
		{
			if (shell->xcmd->pipe_fd[i][0] > 2)
			{
				close(shell->xcmd->pipe_fd[i][0]);
				shell->xcmd->pipe_fd[i][0] = -1;
			}
			if (shell->xcmd->pipe_fd[i][1] > 2)
			{
				close(shell->xcmd->pipe_fd[i][1]);
				shell->xcmd->pipe_fd[i][1] = -1;
			}
		}
		i++;
	}
}

void	close_pipes_child(t_shell *shell, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (shell->xcmd->pipe_fd[i])
		{
			if (shell->xcmd->pipe_fd[i][0] > 2)
				close(shell->xcmd->pipe_fd[i][0]);
			if (shell->xcmd->pipe_fd[i][1] > 2)
				close(shell->xcmd->pipe_fd[i][1]);
		}
		i++;
	}
}

void	close_parent_pipe(t_shell *shell, int i)
{
	if ((i > 0) && (shell->xcmd->pipe_fd[i - 1][0] > 2))
	{
		close(shell->xcmd->pipe_fd[i - 1][0]);
		shell->xcmd->pipe_fd[i - 1][0] = -1;
	}
	if ((i < shell->xcmd->cmd_count - 1) && (shell->xcmd->pipe_fd[i][1] > 2))
	{
		close(shell->xcmd->pipe_fd[i][1]);
		shell->xcmd->pipe_fd[i][1] = -1;
	}
}