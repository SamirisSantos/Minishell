/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:24:40 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/18 22:18:30 by cpinho-c         ###   ########.fr       */
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
	tree->fd_in_type = 0;
	tree->fd_in = 0;
	tree->fd_out_type = 0;
	tree->fd_out = 0;
	tree->heredoc_name = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->type = 0;
	return (tree);
}
