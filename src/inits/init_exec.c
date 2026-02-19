/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:09:07 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/18 22:15:42 by cpinho-c         ###   ########.fr       */
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
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return ;
	}
	while (i < shell->xcmd->cmd_count - 1)
	{
		shell->xcmd->pipe_fd[i] = malloc(2 * sizeof(int));
		if (!shell->xcmd->pipe_fd[i])
		{
			shell->exit_status = 12;
			ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
			close_pipes(shell, i + 1);
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
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return ;
	}
	shell->xcmd->pids = pids;
}

void	init_cmd_path(t_shell *shell)
{
	shell->xcmd->cmd_path = (char **)malloc((shell->xcmd->cmd_count + 1) * sizeof(char *));
	if (!shell->xcmd->cmd_path)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return ;
	}
}

void	init_xcmd(t_shell *shell)
{
	t_xcmd	*xcmd;

	xcmd = malloc(sizeof(t_xcmd));
	if(!xcmd)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return ;
	}
	xcmd->cmd_count = 0;
	xcmd->cmd_path = NULL;
	xcmd->pids = NULL;
	xcmd->pipe_fd = NULL;
	shell->xcmd = xcmd;
}
