/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:41:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/18 22:14:20 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_pipe_pids(t_shell *shell)
{
	if (shell->xcmd->pipe_fd)
	{
		close_pipes(shell, shell->xcmd->cmd_count);
		free(shell->xcmd->pipe_fd);
	}
	if (shell->xcmd->pids)
		free(shell->xcmd->pids);
	if (shell->xcmd)
		free(shell->xcmd);
}
