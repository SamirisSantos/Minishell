/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:19:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:42:39 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_cmd_no_args(t_shell *shell, t_tree *tree)
{
	char	**args;

	if (!tree->data)
	{
		shell->exit_status = 1;
		return ;
	}
	args = (char **)ft_calloc(2, sizeof(char *));
	if (!args)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return ;
	}
	args[0] = ft_strdup(tree->data);
	args[1] = NULL;
	tree->cmd_args = args;
}

void	check_redir(t_shell *shell, t_tree *tree, t_token **token)
{
	t_redir	*temp;

	if (!tree->redir)
		tree->redir = fill_redir(shell, tree, token);
	else
	{
		temp = tree->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = fill_redir(shell, tree, token);
	}
}

t_redir	*fill_redir(t_shell *shell, t_tree *tree, t_token **token)
{
	t_redir	*redir;

	redir = init_redir(shell);
	if ((*token)->type == REDIR_IN || (*token)->type == REDIR_IN_FILE)
	{
		redir->type = (*token)->type;
		if ((*token)->type == REDIR_IN)
			(*token) = (*token)->next;
		redir->filename = ft_strdup((*token)->data);
		(*token) = (*token)->next;
	}
	else if ((*token)->type == REDIR_OUT || (*token)->type == APPEND)
	{
		redir->type = (*token)->type;
		(*token) = (*token)->next;
		redir->filename = ft_strdup((*token)->data);
		(*token) = (*token)->next;
	}
	else if ((*token)->type == HEREDOC)
	{
		redir->type = (*token)->type;
		redir->filename = get_heredoc_info(shell, tree, token);
	}
	return (redir);
}

static char	**create_args_array(t_shell *shell, t_token *tokens)
{
	char	**args;
	int		arg_count;

	arg_count = 0;
	while (tokens && tokens->type == CMD_ARG)
	{
		tokens = tokens->next;
		arg_count++;
	}
	args = (char **)ft_calloc(arg_count + 2, sizeof(char *));
	if (!args)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return (NULL);
	}
	return (args);
}

char	**build_args(t_shell *shell, t_token **tokens)
{
	char	**args;
	int		i;

	args = create_args_array(shell, *tokens);
	args[0] = NULL;
	i = 1;
	while ((*tokens) && (*tokens)->type == CMD_ARG)
	{
		args[i] = ft_strdup((*tokens)->data);
		(*tokens) = (*tokens)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
