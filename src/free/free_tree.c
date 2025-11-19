/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:10:32 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/19 13:41:43 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tree(t_tree *tree)
{
	if(!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->data);
	free_array(tree->cmd_args);
	free(tree);
}
