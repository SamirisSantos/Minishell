/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:35:11 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:39:26 by cpinho-c         ###   ########.fr       */
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
		if (shell->xcmd->cmd_path)
			free_array(shell->xcmd->cmd_path);
		free_pipe_pids(shell);
		free(shell->xcmd);
		shell->xcmd = NULL;
	}
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->heredoc_count > 0)
		clear_heredoc(shell->tree);
	if (shell->tree)
		free_tree(shell->tree);
	if (shell->token)
		free_tokens(shell->token);
	free(shell);
}
