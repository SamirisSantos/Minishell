/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:22:17 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/01/20 16:26:58 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clear_heredoc(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->heredoc_name)
	{
		unlink(tree->heredoc_name);
		free(tree->heredoc_name);
	}
	clear_heredoc(tree->left);
	clear_heredoc(tree->right);
}
