/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:28:49 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/03/02 15:02:16 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_redir_count(t_redir *temp)
{
	int	i;

	i = 0;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

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
	shell->exit_status = 1;
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
		return (0);
	}
	shell->exit_status = 1;
	ft_printf(STDOUT_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
	return (-2);
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
	shell->exit_status = 0;
	return (0);
}
