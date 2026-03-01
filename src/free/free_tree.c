/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:10:32 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/24 15:03:14 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->data)
		free(tree->data);
	if (tree->cmd_args)
		free_array(tree->cmd_args);
	if (tree->heredoc_eof)
		free(tree->heredoc_eof);
	if (tree->redir)
		free_redir(tree->redir);
	free(tree);
}
