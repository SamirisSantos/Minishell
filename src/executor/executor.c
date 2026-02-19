/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:48 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/09 16:07:04 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	executor(t_shell *shell, t_tree *tree, int i)
{
	pid_t	pid;
	
	if (i < shell->xcmd->cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(shell->xcmd->pipe_fd[i - 1][0], STDIN_FILENO);
			if (i < shell->xcmd->cmd_count - 1)
				dup2(shell->xcmd->pipe_fd[i][1], STDOUT_FILENO);
			close_pipes(shell);
			execve(shell->xcmd->cmd_path[i],tree->cmd_args,shell->envp_cpy);
			ft_printf(STDERR_FILENO, "%s: %s", tree->data, strerror(errno));
			free_shell(shell);
			if (errno == ENOENT)
				exit(127);
			else
				exit(126);
		}
		else if (pid > 0)
			shell->xcmd->pids[i] = pid;
	}
}

void	start_exe(t_shell *shell, t_tree *tree, int *i)
{
	if (!tree)
		return ;
	if (tree->type == PIPE)
	{
		if (pipe(shell->xcmd->pipe_fd[*i]) == -1)
		{
			ft_printf(STDERR_FILENO, "%s", strerror(errno));
			shell->exit_status = 1;
			return ;
		}
	}
	if(tree->type == CMD)
	{
		shell->xcmd->cmd_path[*i] = find_cmd_path(shell, tree);
		if(is_builtin(tree) && shell->xcmd->cmd_count > 1)
			fork_builtin(shell, tree, *i);
		else if (is_builtin(tree) && shell->xcmd->cmd_count == 1)
			exec_builtin(shell, tree);
		else
			executor(shell, tree, *i);
		(*i)++;
	}
	start_exe(shell, tree->left, i);
	start_exe(shell, tree->right, i);
}

void	pre_executor(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	init_xcmd(shell);
	count_cmds(shell->tree, &shell->xcmd->cmd_count);
	init_pipes(shell);
	init_pid(shell);
	init_cmd_path(shell);
	start_exe(shell, shell->tree, &i);
	i = 0;
	while (i < shell->xcmd->cmd_count - 1)
	{
		close(shell->xcmd->pipe_fd[i][0]);
		close(shell->xcmd->pipe_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < shell->xcmd->cmd_count)
	{
		waitpid(shell->xcmd->pids[i], &status, 0);
		shell->exit_status = status >> 8;
		i++;
	}
}
