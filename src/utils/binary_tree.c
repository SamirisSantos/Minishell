/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2025-10-16 15:36:21 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/minishell.h"

t_tree	*build_tree(t_token *tokens)
{
	t_token	*temp = tokens;
	t_token *check_pipe = tokens;
	t_token	*scan = tokens;

	while (check_pipe && check_pipe->type != PIPE)
		check_pipe = check_pipe->next;
	if (check_pipe && check_pipe->type == PIPE)
	{
		t_tree	*tree = newnode(check_pipe);
		tree->left = build_tree(temp);
		tree->right = build_tree(check_pipe->next);
		return (tree);
	}
	t_tree	*tree = NULL;
	if (temp && temp->type == REDIR_IN_FILE)
	{
		scan = temp;
		while (temp && (temp->type == REDIR_IN_FILE || temp->type == REDIR_IN))
			temp = temp->next;
		if (temp && temp->type == CMD)
			tree = newnode(temp);
		if (temp && temp->next == CMD_ARG)
			tree->cmd_args = build_args(temp->next);
		tree->redir_in = true;
		tree->fd_in = ft_redir(scan,scan->next);
	}
	if (temp && temp->type == CMD)
	if (temp && temp->next == CMD_ARG)
		tree->cmd_args = build_args(temp->next);
	while (temp && (temp->type == CMD || temp->type == CMD_ARG))
		temp = temp->next;
	if (temp && temp == REDIR_OUT && temp->next == REDIR_OUT_FILE)
	{
		tree->redir_out = true;
		tree->fd_out = ft_redir(temp->next, temp);
	}
	return (tree);
}