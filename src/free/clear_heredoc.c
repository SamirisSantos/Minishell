/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:22:17 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/26 11:45:22 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clear_heredoc(t_tree *tree)
{
	if (!tree)
		return ;
	while (tree->redir && tree->redir->type == HEREDOC)
	{
		unlink(tree->redir->filename);
		tree->redir = tree->redir->next;
	}
	clear_heredoc(tree->left);
	clear_heredoc(tree->right);
}
