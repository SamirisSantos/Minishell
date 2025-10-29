/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:24:40 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/29 18:23:10 by cpinho-c         ###   ########.fr       */
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
		ft_printf(STDERR_FILENO, "%s", ERROR_MALLOC);
		return(NULL);
	}
	tree->cmd_args = NULL;
	tree->data = NULL;
	tree->fd_in = NULL;
	tree->fd_out = 1;
	tree->left = NULL;
	tree->redir_in = false;
	tree->redir_out = false;
	tree->right = NULL;
	tree->type = NULL;
	return (tree);
}
