/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:09:07 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:39:39 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_pid(t_shell *shell)
{
	pid_t	*pids;
	int		i;

	pids = ft_calloc(shell->xcmd->cmd_count, sizeof(pid_t));
	if (!pids)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return ;
	}
	i = 0;
	while (i < shell->xcmd->cmd_count)
		pids[i++] = -1;
	shell->xcmd->pids = pids;
}

void	init_cmd_path(t_shell *shell)
{
	shell->xcmd->cmd_path = (char **)ft_calloc((shell->xcmd->cmd_count + 1),
			sizeof(char *));
	if (!shell->xcmd->cmd_path)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return ;
	}
}

void	init_xcmd(t_shell *shell)
{
	t_xcmd	*xcmd;

	xcmd = malloc(sizeof(t_xcmd));
	if (!xcmd)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return ;
	}
	xcmd->cmd_count = 0;
	xcmd->cmd_path = NULL;
	xcmd->pids = NULL;
	xcmd->pipe_fd = NULL;
	shell->xcmd = xcmd;
}
