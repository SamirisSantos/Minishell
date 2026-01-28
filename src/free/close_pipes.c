/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:36:39 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/01/13 17:36:39 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->xcmd->cmd_count - 1)
	{
		close(shell->xcmd->pipe_fd[i][0]);
		close(shell->xcmd->pipe_fd[i][1]);
		free(shell->xcmd->pipe_fd[i]);
		i++;
	}
}
