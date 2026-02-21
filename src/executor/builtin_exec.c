/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:30:06 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/21 22:44:31 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_builtin(t_tree *tree)
{
	if (((strncmp(tree->data, "cd", 2) == 0) && ft_strlen(tree->data) == 2) ||
		((strncmp(tree->data, "echo", 4) == 0) && ft_strlen(tree->data) == 4) ||
		((strncmp(tree->data, "env", 3) == 0) && ft_strlen(tree->data) == 3) ||
		((strncmp(tree->data, "exit", 4) == 0) && ft_strlen(tree->data) == 4) ||
		((strncmp(tree->data, "export", 6) == 0) && ft_strlen(tree->data) == 6) ||
		((strncmp(tree->data, "pwd", 3) == 0) && ft_strlen(tree->data) == 3) ||
		((strncmp(tree->data, "unset", 5) == 0) && ft_strlen(tree->data) == 5))
		return (true);
	else
		return (false);
}

void	exec_builtin(t_shell *shell, t_tree *tree)
{
	 if (tree->fd_in > 0)
		dup2(tree->fd_in, STDIN_FILENO);
	if (tree->fd_out != STDOUT_FILENO)
		dup2(tree->fd_out, STDOUT_FILENO);
	if (strncmp(tree->data, "cd", 2) == 0 && ft_strlen(tree->data) == 2)
		{
	if (tree->cmd_args && tree->cmd_args[1])
		ft_cd(shell, tree->cmd_args[1]);
	else
		ft_cd(shell, NULL);
	}
	else if (strncmp(tree->data, "echo", 4) == 0 && ft_strlen(tree->data) == 4)
		ft_echo(shell, tree);
	else if (strncmp(tree->data, "env", 3) == 0 && ft_strlen(tree->data) == 3)
		ft_env(shell);
	else if (strncmp(tree->data, "exit", 4) == 0 && ft_strlen(tree->data) == 4)
		ft_exit(shell);
	else if (strncmp(tree->data, "export", 6) == 0 && ft_strlen(tree->data) == 6)
		ft_export(shell, tree->cmd_args);
	else if (strncmp(tree->data, "pwd", 3) == 0 && ft_strlen(tree->data) == 3)
		ft_pwd(shell, tree);
	else if (strncmp(tree->data, "unset", 5) == 0 && ft_strlen(tree->data) == 5)
		ft_unset(shell, tree->cmd_args);
}

void	fork_builtin(t_shell *shell, t_tree *tree, int i)
{
	pid_t	pid;
	int		exit_status;

	if (i < shell->xcmd->cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (tree->fd_in > 0)
			{
				dup2(tree->fd_in, STDIN_FILENO);
				close(tree->fd_in);
			}
			if (i > 0)
				dup2(shell->xcmd->pipe_fd[i - 1][0], STDIN_FILENO);
			if (i < shell->xcmd->cmd_count - 1)
				dup2(shell->xcmd->pipe_fd[i][1], STDOUT_FILENO);
			exec_builtin(shell, tree);
			exit_status = shell->exit_status;
			free_shell(shell);
			exit(exit_status);
		}
		else if (pid > 0)
			shell->xcmd->pids[i] = pid;
	}
}
