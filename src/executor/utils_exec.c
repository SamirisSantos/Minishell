/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:56:13 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/22 20:56:13 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	save_and_redirect(t_tree *tree, int *saved_stdin)
{
	int	saved_stdout;

	*saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (tree->fd_in > 0)
	{
		dup2(tree->fd_in, STDIN_FILENO);
		close(tree->fd_in);
	}
	if (tree->fd_out != STDOUT_FILENO)
	{
		dup2(tree->fd_out, STDOUT_FILENO);
		close(tree->fd_out);
	}
	return (saved_stdout);
}

void	restore_fds(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}
void	close_pipes_child(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->xcmd->cmd_count - 1)
	{
		close(shell->xcmd->pipe_fd[i][0]);
		close(shell->xcmd->pipe_fd[i][1]);
		i++;
	}
}

void	execve_error(t_shell *shell, t_tree *tree)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->data, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_shell(shell);
	if (errno == EACCES)
		exit(126);
	exit(127);
}