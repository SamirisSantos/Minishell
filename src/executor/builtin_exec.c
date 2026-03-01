/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:30:06 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/22 21:02:41 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_builtin(t_tree *tree)
{
	if (((strncmp(tree->data, "cd", 2) == 0) && ft_strlen(tree->data) == 2)
		|| ((strncmp(tree->data, "echo", 4) == 0) && ft_strlen(tree->data) == 4)
		|| ((strncmp(tree->data, "env", 3) == 0) && ft_strlen(tree->data) == 3)
		|| ((strncmp(tree->data, "exit", 4) == 0) && ft_strlen(tree->data) == 4)
		|| ((strncmp(tree->data, "export", 6) == 0)
			&& ft_strlen(tree->data) == 6)
		|| ((strncmp(tree->data, "pwd", 3) == 0)
			&& ft_strlen(tree->data) == 3)
		|| ((strncmp(tree->data, "unset", 5) == 0)
			&& ft_strlen(tree->data) == 5))
		return (true);
	else
		return (false);
}

static void	run_builtin(t_shell *shell, t_tree *tree)
{
	if (strncmp(tree->data, "cd", 2) == 0 && ft_strlen(tree->data) == 2)
		exec_cd(shell, tree);
	else if (strncmp(tree->data, "echo", 4) == 0 && ft_strlen(tree->data) == 4)
		ft_echo(shell, tree);
	else if (strncmp(tree->data, "env", 3) == 0 && ft_strlen(tree->data) == 3)
		ft_env(shell, tree);
	else if (strncmp(tree->data, "exit", 4) == 0 && ft_strlen(tree->data) == 4)
		ft_exit(shell, tree);
	else if (strncmp(tree->data, "export", 6) == 0
		&& ft_strlen(tree->data) == 6)
		ft_export(shell, tree->cmd_args);
	else if (strncmp(tree->data, "pwd", 3) == 0 && ft_strlen(tree->data) == 3)
		ft_pwd(shell, tree);
	else if (strncmp(tree->data, "unset", 5) == 0 && ft_strlen(tree->data) == 5)
		ft_unset(shell, tree->cmd_args);
}

void	exec_builtin(t_shell *shell, t_tree *tree, bool is_child)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = save_and_redirect(&saved_stdin);
	if (is_child)
		apply_child_redirects(shell, tree);
	else
	{
		if (apply_redirects(shell, tree) == -2)
		{
			restore_fds(saved_stdout, saved_stdin);
			return ;
		}
	}
	run_builtin(shell, tree);
	restore_fds(saved_stdout, saved_stdin);
}

static void	child_builtin(t_shell *shell, t_tree *tree, int i)
{
	int	exit_status;

	if (i > 0)
		dup2(shell->xcmd->pipe_fd[i - 1][0], STDIN_FILENO);
	if (i < shell->xcmd->cmd_count - 1)
		dup2(shell->xcmd->pipe_fd[i][1], STDOUT_FILENO);
	exec_builtin(shell, tree, true);
	exit_status = shell->exit_status;
	free_shell(shell);
	exit(exit_status);
}

void	fork_builtin(t_shell *shell, t_tree *tree, int i)
{
	pid_t	pid;

	if (i >= shell->xcmd->cmd_count)
		return ;
	pid = fork();
	if (pid == 0)
		child_builtin(shell, tree, i);
	else if (pid > 0)
	{
		shell->xcmd->pids[i] = pid;
		close_parent_pipe(shell, i);
	}
}
