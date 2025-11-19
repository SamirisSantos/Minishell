/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:10:32 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/18 16:56:31 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_pipe_pids(t_xcmd *xcmd)
{
	int	i;

	i = 0;
	if (xcmd->pipe_fd)
	{
		while (i < xcmd->cmd_count - 1)
		{
			close(xcmd->pipe_fd[i][0]);
			close(xcmd->pipe_fd[i][1]);
			free(xcmd->pipe_fd[i]);
			i++;
		}
		free(xcmd->pipe_fd);
	}
	if (xcmd->pids)
		free(xcmd->pids);
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
		free(token);
		token = temp;
	}
}

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