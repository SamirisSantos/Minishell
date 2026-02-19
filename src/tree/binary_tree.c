/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:36:21 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 16:25:47 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*build_node(t_shell *shell, t_token *tokens, t_tree *tree)
{
	if ((tokens) && (tokens->type == REDIR_IN_FILE || tokens->type == REDIR_OUT
		|| tokens->type == APPEND))
		check_redir(shell, tree, &tokens);
	// if (tokens->type == HEREDOC && tokens->next->type == DELIMITER)
	// 	handle_heredoc(shell, tree, &tokens);
	if ((tokens) && tokens->type == CMD)
	{
		tree->data = tokens->data;
		tree->type = tokens->type;
		tokens = tokens->next;
	}
	if ((tokens) && tokens->type == CMD_ARG)
	{
		tree->cmd_args = build_args(&tokens);
		if (tree->data)
			tree->cmd_args[0] = ft_strdup(tree->data);
	}
	return (tree);
}

t_tree	*build_tree_pipe(t_shell *shell, t_tree *tree, t_token *tokens, t_token *pipe)
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
/////////////////

// t_token	*new_test_token(char *data, t_token_type type)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->data = ft_strdup(data);
// 	new->type = type;
// 	new->next = NULL;
// 	return (new);
// }

// t_token	*mock_redir_test(void)
// {
// 	t_token	*list = NULL;

// 	list = new_test_token("ls", CMD);
// 	list->next = new_test_token(">", REDIR_OUT);
// 	list->next->next = new_test_token("outfile.txt", REDIR_OUT_FILE);
// 	list->next->next->next = new_test_token("|", PIPE);
// 	list->next->next->next->next = new_test_token("cat", CMD);
// 	list->next->next->next->next->next = new_test_token("file", CMD_ARG);
// 	list->next->next->next->next->next->next = new_test_token("|", PIPE);
// 	list->next->next->next->next->next->next->next = new_test_token("grep", CMD);
// 	list->next->next->next->next->next->next->next->next = new_test_token("hello", CMD_ARG);
// 	list->next->next->next->next->next->next->next->next->next = new_test_token(">>", APPEND);
// 	list->next->next->next->next->next->next->next->next->next->next = new_test_token("out", REDIR_OUT_FILE);
// 	return (list);
// }
// void	print_tree(t_tree *tree)
// {
// 	if(!tree)
// 		return ;
// 	printf("%s, %d\n", tree->data, tree->type);
// 	print_tree(tree->left);
// 	print_tree(tree->right);
// }

// int main (int ac, char **av, char *envp[])
// {
// 	t_token *test_list;
//     t_tree  *tree_root;
// 	t_shell	*shell;
	
// 	shell = init_shell();
// 	shell->tree = tree_root;
//     test_list = mock_redir_test();
	
//     tree_root = build_tree(shell, test_list, false);
//     if (tree_root)
// 	{
//         printf("Tree built successfully!\n");
// 		print_tree(tree_root);
// 		free_shell(shell);
// 	}
//     return (0);
// }