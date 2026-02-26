/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:48 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:39:03 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	**get_argv(t_tree *tree, char **fallback)
{
	if (tree->cmd_args)
		return (tree->cmd_args);
	fallback[0] = tree->data;
	fallback[1] = NULL;
	return (fallback);
}

static void	child_executor(t_shell *shell, t_tree *tree, int i, char **argv)
{
	if (i > 0)
		dup2(shell->xcmd->pipe_fd[i - 1][0], STDIN_FILENO);
	if (i < shell->xcmd->cmd_count - 1)
		dup2(shell->xcmd->pipe_fd[i][1], STDOUT_FILENO);
	apply_child_redirects(shell, tree);
	close_pipes_child(shell, shell->xcmd->cmd_count - 1);
	execve(shell->xcmd->cmd_path[i], argv, shell->envp_cpy);
	execve_error(shell, tree);
}

void	executor(t_shell *shell, t_tree *tree, int i)
{
	pid_t	pid;
	char	*fallback[2];

	if (check_cmd(shell, tree, i) != 0)
		return ;
	if (i >= shell->xcmd->cmd_count)
		return ;
	pid = fork();
	if (pid == 0)
		child_executor(shell, tree, i, get_argv(tree, fallback));
	else if (pid > 0)
	{
		shell->xcmd->pids[i] = pid;
		close_parent_pipe(shell, i);
	}
}
