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

int	save_and_redirect(int *saved_stdin)
{
	int	saved_stdout;

	*saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	return (saved_stdout);
}

void	restore_fds(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
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

void	apply_child_redirects(t_shell *shell, t_tree *tree)
{
	int	fd;
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN)
		{
			fd = ft_redir_in(shell, temp->filename);
			if (fd < 0)
				exit (1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (temp->type == REDIR_OUT || temp->type == APPEND)
		{
			fd = ft_redir_out(shell, temp->filename, temp->type);
			if (fd < 0)
				exit (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		temp = temp->next;
	}
}

int	apply_redirects(t_shell *shell, t_tree *tree)
{
	int	fd;
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN)
		{
			fd = ft_redir_in(shell, temp->filename);
			if (fd < 0)
				return (-2);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (temp->type == REDIR_OUT || temp->type == APPEND)
		{
			fd = ft_redir_out(shell, temp->filename, temp->type);
			if (fd < 0)
				return (-2);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		temp = temp->next;
	}
	return (0);
}
