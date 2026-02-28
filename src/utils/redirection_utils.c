/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:28:49 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/28 18:30:53 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	apply_child_redirects(t_shell *shell, t_tree *tree)
{
	int		fd;
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == HEREDOC)
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
	int		fd;
	t_redir	*temp;

	temp = tree->redir;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == HEREDOC)
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
