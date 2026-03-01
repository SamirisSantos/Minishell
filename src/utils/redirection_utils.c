/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:28:49 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/03/01 12:20:52 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	valid_redir_in(t_shell *shell, char *filename)
{
	int	fd;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == 0)
		{
			fd = ft_redir_in(shell, filename);
			if (fd < 0)
				return (-2);
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (0);
		}
	}
	ft_printf(STDOUT_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
	return (-2);
}

static int	valid_redir_out(t_shell *shell, char *filename, t_token_type type)
{
	int	fd;

	if (access(filename, F_OK) != 0 || ((access(filename, F_OK) == 0)
		&& (access(filename, W_OK) == 0)))
	{
		fd = ft_redir_out(shell, filename, type);
		if (fd < 0)
			return (-2);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	ft_printf(STDOUT_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
	return (-2);
}

void	apply_child_redirects(t_shell *shell, t_tree *tree)
{
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == HEREDOC)
		{
			if (valid_redir_in(shell, temp->filename) == -2)
				exit (1);
		}
		if (temp->type == REDIR_OUT || temp->type == APPEND)
		{
			if (valid_redir_out(shell, temp->filename, temp->type) == -2)
				exit (1);
		}
		temp = temp->next;
	}
}

int	apply_redirects(t_shell *shell, t_tree *tree)
{
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == HEREDOC)
		{
			if (valid_redir_in(shell, temp->filename) == -2)
				return (-2);
		}
		if (temp->type == REDIR_OUT || temp->type == APPEND)
		{
			if (valid_redir_out(shell, temp->filename, temp->type) == -2)
				return (-2);
		}
		temp = temp->next;
	}
	return (0);
}
