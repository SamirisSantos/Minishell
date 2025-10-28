/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/28 18:53:16 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left)
{
	t_token *check_pipe = tokens;
	t_tree	*tree;

	while (check_pipe && check_pipe->type != PIPE && is_left == false)
		check_pipe = check_pipe->next;
	if (check_pipe && check_pipe->type == PIPE)
	{
		tree = newnode(check_pipe);
		tree->left = build_tree(shell, tokens, true);
		tree->right = build_tree(shell, check_pipe->next, false);
		return (tree);
	}
	if (tokens)
	{
		tree = init_tree_node();
		if (tokens->type == REDIR_IN_FILE || tokens->type == REDIR_OUT)
			check_redir(shell, tree, &tokens);
		if (tokens->type == CMD)
		{
			tree->data = tokens->data;
			tree->type = tokens->type;
			tokens = tokens->next;
		}
		if (tokens->type == CMD_ARG)
			tree->cmd_args = build_args(&tokens);
	}
	return (tree);
}


