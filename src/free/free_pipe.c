/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:41:18 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 13:41:28 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_pipe_pids(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->xcmd->pipe_fd)
	{
		while (i < shell->xcmd->cmd_count - 1)
		{
			close(shell->xcmd->pipe_fd[i][0]);
			close(shell->xcmd->pipe_fd[i][1]);
			free(shell->xcmd->pipe_fd[i]);
			i++;
		}
		free(shell->xcmd->pipe_fd);
	}
	if (shell->xcmd->pids)
		free(shell->xcmd->pids);
	if (shell->xcmd)
		free(shell->xcmd);
}