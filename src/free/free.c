/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:10:32 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/13 18:07:37 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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


void	free_tree(t_tree *tree)
{
	if(!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->data);
	free_array(tree->cmd_args);
	free(tree);
}

void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		if (token->data)
			free(token->data);
		free(token);
		token = temp;
	}
}

void	free_shell(t_shell *shell)
{
	free(shell->cwd);
	free_array(shell->envp_cpy);
	free_pipe_pids(shell);
	free_tree(shell->tree);
	free_token(shell->token);
	free(shell);
}