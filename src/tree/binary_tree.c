/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:41:21 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_cmd_arg(t_shell *shell, t_tree *tree, t_token **tokens)
{
	tree->cmd_args = build_args(shell, tokens);
	if (tree->data && tree->cmd_args)
		tree->cmd_args[0] = ft_strdup(tree->data);
}

static int	is_redir(t_token_type type)
{
	return (type == REDIR_OUT || type == APPEND
		|| type == REDIR_IN || type == REDIR_IN_FILE
		|| type == HEREDOC);
}

t_tree	*build_node(t_shell *shell, t_token *tokens, t_tree *tree)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
			check_redir(shell, tree, &tokens);
		else if (tokens->type == CMD)
		{
			tree->data = tokens->data;
			tree->type = tokens->type;
			tokens = tokens->next;
		}
		else if (tokens->type == CMD_ARG)
			handle_cmd_arg(shell, tree, &tokens);
		else
			tokens = tokens->next;
	}
	return (tree);
}

t_tree	*build_tree_pipe(t_shell *shell, t_tree *tree, t_token *tokens,
		t_token *pipe)
{
	t_token	*cut;

	cut = tokens;
	while (cut && cut->next && cut->next->type != PIPE)
		cut = cut->next;
	if (cut && cut->next && cut->next->type == PIPE)
		cut->next = NULL;
	tree->data = pipe->data;
	tree->type = PIPE;
	tree->right = build_tree(shell, pipe->next, false);
	tree->left = build_tree(shell, tokens, true);
	return (tree);
}

t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left)
{
	t_token	*check_pipe;
	t_tree	*tree;

	check_pipe = tokens;
	tree = init_tree_node(shell);
	if (!tokens)
	{
		shell->exit_status = 1;
		return (NULL);
	}
	while (check_pipe && check_pipe->type != PIPE && is_left == false)
		check_pipe = check_pipe->next;
	if (check_pipe && check_pipe->type == PIPE)
		tree = build_tree_pipe(shell, tree, tokens, check_pipe);
	else if (tokens)
		tree = build_node(shell, tokens, tree);
	return (tree);
}
