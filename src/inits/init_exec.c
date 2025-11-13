/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:09:07 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/11 17:02:03 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->xcmd->cmd_count - 1 <= 0)
		return ;
	shell->xcmd->pipe_fd = malloc((shell->xcmd->cmd_count - 1) * sizeof(int *));
	if(!shell->xcmd->pipe_fd)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "%s", ERROR_MALLOC);
		return ;
	}
	while (i < shell->xcmd->cmd_count - 1)
	{
		shell->xcmd->pipe_fd[i] = malloc(2 * sizeof(int));
		if (!shell->xcmd->pipe_fd[i])
		{
			shell->exit_status = 12;
			ft_printf(STDERR_FILENO, "%s", ERROR_MALLOC);
			free_pipe(shell, i + 1);
			return ;
		}
		i++;
	}
}

void	init_pid(t_shell *shell)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * shell->xcmd->cmd_count);
	if (!pids)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "%s", ERROR_MALLOC);
		return ;
	}
	shell->xcmd->pids = pids;
}
