/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/12 15:46:10 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*build_node(t_shell *shell, t_token *tokens)
{
	t_tree	*tree;

	tree = init_tree_node(shell);
	if (!tokens)
		return (tree);
	if (tokens->type == REDIR_IN_FILE || tokens->type == REDIR_OUT
		|| tokens->type == APPEND)
		check_redir(shell, tree, &tokens);
	if (tokens && tokens->type == HEREDOC && tokens->next
		&& tokens->next->type == DELIMITER)
		handle_heredoc(shell, tree, &tokens);
	if (tokens && tokens->type == CMD)
	{
		tree->data = tokens->data;
		tree->type = tokens->type;
		tokens = tokens->next;
	}
	if (tokens && tokens->type == CMD_ARG)
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
	tree = build_node(shell, tokens);
	return (tree);
}
