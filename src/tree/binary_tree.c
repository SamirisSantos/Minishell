/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/29 17:27:13 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*build_node(t_shell *shell, t_token *tokens)
{
	t_tree	*tree;

	tree = init_tree_node(shell);
	if (tokens->type == REDIR_IN_FILE || tokens->type == REDIR_OUT
		|| tokens->type == APPEND)
		check_redir(shell, tree, &tokens);
	if (tokens->type == HEREDOC && tokens->next->type == DELIMITER)
		create_heredoc(shell, tree, tokens);
	if (tokens->type == CMD)
	{
		tree->data = tokens->data;
		tree->type = tokens->type;
		tokens = tokens->next;
	}
	if (tokens->type == CMD_ARG)
	{
		tree->cmd_args = build_args(&tokens);
		if (tree->data)
			tree->cmd_args[0] = ft_strdup(tree->data);
	}
	return (tree);
}

t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left)
{
	t_token	*check_pipe;
	t_tree	*tree;

	check_pipe = tokens;
	if (!tokens)
	{
		shell->exit_status = 1;
		return (NULL);
	}
	while (check_pipe && check_pipe->type != PIPE && is_left == false)
		check_pipe = check_pipe->next;
	if (check_pipe && check_pipe->type == PIPE)
	{
		tree = init_tree_node(shell);
		tree->data = tokens->data;
		tree->left = build_tree(shell, tokens, true);
		tree->right = build_tree(shell, check_pipe->next, false);
		return (tree);
	}
	if (tokens)
		tree = build_node(shell, tokens);
	return (tree);
}
