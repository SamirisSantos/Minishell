/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:48 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/18 20:12:19 by cpinho-c         ###   ########.fr       */
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

bool	is_builtin(t_tree *tree)
{
	if ((strncmp(tree->data, "cd", 2) && ft_strlen(tree->data == 2)) ||
		(strncmp(tree->data, "echo", 4) && ft_strlen(tree->data == 4)) ||
		(strncmp(tree->data, "echo", 4) && ft_strlen(tree->data == 4)) ||
		
		
		)
		return (true);
	if (strncmp(tree->data, "echo", 4) && ft_strlen(tree->data == 4))
		return (true);
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
		shell->xcmd->cmd_path[*i] = find_cmd_path(tree);
		if(builtins(shell))
			//function to exec the specific builtin
		else
			executor(shell, tree, i); // only for not builtins
		i++;
	}
	start_exe(shell, tree->left, i);
	start_exe(shell, tree->right, i);
}

void	pre_executor(t_shell *shell)
{
	init_xcmd(shell);
	count_cmds(shell->tree, &shell->xcmd->cmd_count);
	init_pipes(shell);
	init_pid(shell);
	init_cmd_path(shell);
	start_exe(shell, shell->tree, 0);
}

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
			close(shell->xcmd->pipe_fd[i][0]);
			close(shell->xcmd->pipe_fd[i][1]);
			execve(tree->data, shell->xcmd->cmd_path[i],shell->envp_cpy);
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
