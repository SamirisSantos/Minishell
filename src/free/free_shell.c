/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:35:11 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 14:37:48 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void	free_shell(t_shell *shell)
{
	if (shell->cwd)
		free(shell->cwd);
	if (shell->envp_cpy)
		free_array(shell->envp_cpy);
	if (shell->xcmd)
	{
		if(shell->xcmd->cmd_path)
			free_array(shell->xcmd->cmd_path);
		if(shell->xcmd->pids || shell->xcmd->pipe_fd)
			free_pipe_pids(shell->xcmd->pids);
		free(shell->xcmd);
	}
	if (shell->tree)
		free_tree(shell->tree);
	if (shell->token)
		free_token(shell->token);
	free(shell);
}
