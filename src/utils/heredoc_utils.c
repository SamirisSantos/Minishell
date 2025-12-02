/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:56:37 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/12/02 16:56:37 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	create_heredoc(t_shell *shell, t_tree *tree, t_token **token)
{
	tree->fd_in_type == (*token)->type;
	tree->fd_in = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tree->fd_in == -1)
	{
		shell->exit_status = 1;
		ft_printf(STDERR_FILENO, "%s", strerror(errno));
	}
	(*token) = (*token)->next;
	if ((*token)->type == DELIMITER)
	{
		build_heredoc(shell, tree, (*token)->data);
		(*token) = (*token)->next;
	}
}

void	build_heredoc(t_shell *shell, t_tree *tree, char *delimiter)
{
	
}