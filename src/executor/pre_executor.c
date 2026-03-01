/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:34:46 by sade-ara          #+#    #+#             */
/*   Updated: 2026/03/01 12:26:06 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_no_cmd(t_shell *shell, t_tree *tree, int *i)
{
	pid_t	pid;

	if (*i < shell->xcmd->cmd_count - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			apply_child_redirects(shell, tree);
			close_pipes_child(shell, shell->xcmd->cmd_count - 1);
			free_shell(shell);
			exit(0);
		}
		else if (pid > 0)
		{
			shell->xcmd->pids[*i] = pid;
			close_parent_pipe(shell, *i);
		}
	}
	else
		apply_redirects(shell, tree);
	(void)tree;
	shell->exit_status = 1;
	(*i)++;
}

void	start_exe(t_shell *shell, t_tree *tree, int *i)
{
	if (!tree)
		return ;
	if (!tree->data)
	{
		handle_no_cmd(shell, tree, i);
		return ;
	}
	if (tree->type == CMD)
	{
		shell->xcmd->cmd_path[*i] = find_cmd_path(shell, tree);
		if (is_builtin(tree) && shell->xcmd->cmd_count > 1)
			fork_builtin(shell, tree, *i);
		else if (is_builtin(tree) && shell->xcmd->cmd_count == 1)
			exec_builtin(shell, tree, false);
		else
			executor(shell, tree, *i);
		(*i)++;
	}
	start_exe(shell, tree->left, i);
	start_exe(shell, tree->right, i);
}

static void	exec_inits(t_shell *shell)
{
	init_xcmd(shell);
	count_cmds(shell->tree, &shell->xcmd->cmd_count);
	init_pipes(shell);
	init_pid(shell);
	init_cmd_path(shell);
}

void	pre_executor(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	exec_inits(shell);
	start_exe(shell, shell->tree, &i);
	i = 0;
	while (i < shell->xcmd->cmd_count)
	{
		if (shell->xcmd->pids[i] != -1)
		{
			waitpid(shell->xcmd->pids[i], &status, 0);
			shell->exit_status = status >> 8;
		}
		i++;
	}
	if (shell->xcmd->cmd_path)
		free_cmd_path(shell);
	shell->xcmd->cmd_path = NULL;
	free_pipe_pids(shell);
	free(shell->xcmd);
	shell->xcmd = NULL;
}
