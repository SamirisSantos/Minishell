/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:48 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/11 16:45:05 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	count_cmds(t_tree *temp, int *cmd_count)
{
	if (!temp)
		return ;
	if (temp->type == CMD)
		(*cmd_count)++;
	count_cmds(temp->left, cmd_count);
	count_cmds(temp->right, cmd_count);
}


void	pre_executor(t_shell *shell)
{
	count_cmds(shell->tree, &shell->cmd_count);
	init_pipes(shell);
	init_pid(shell);
	
}

