/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:24:40 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/19 14:20:35 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*init_tree_node(t_shell *shell)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return (NULL);
	}
	tree->cmd_args = NULL;
	tree->data = NULL;
	tree->fd_in_type = NULL;
	tree->fd_in = NULL;
	tree->fd_out_type = NULL;
	tree->fd_out = 1;
	tree->heredoc_name = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->type = NULL;
	return (tree);
}
