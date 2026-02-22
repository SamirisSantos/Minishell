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

void	check_redir(t_shell *shell, t_tree *tree, t_token **token)
{
	if ((*token)->type == REDIR_IN || (*token)->type == REDIR_IN_FILE)
	{
		tree->fd_in_type = (*token)->type;
		if ((*token)->type == REDIR_IN)
			(*token) = (*token)->next;
		tree->fd_in = ft_redir_in(shell, (*token)->data);
		(*token) = (*token)->next;
	}
	else if ((*token)->type == REDIR_OUT || (*token)->type == APPEND)
	{
		tree->fd_out_type = (*token)->type;
		(*token) = (*token)->next;
		tree->fd_out = ft_redir_out(shell, (*token)->data, tree->fd_out_type);
		(*token) = (*token)->next;
	}
	else if ((*token)->type == HEREDOC)
		(*token) = (*token)->next->next;
}

int	ft_redir_out(t_shell *shell, char *filename, t_token_type type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (fd);
}

int	ft_redir_in(t_shell *shell, char *filename)
{
	int	fd;

	fd = -1;
	if (access(filename, F_OK) == 0)
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (fd);
}

char	**build_args(t_token **tokens)
{
	char	**args;
	t_token	*temp;
	int		arg_count;
	int		i;

	temp = *tokens;
	arg_count = 0;
	while (temp && temp->type == CMD_ARG)
	{
		temp = temp->next;
		arg_count++;
	}
	args = (char **)malloc((arg_count + 2) * sizeof(char *));
	if (!args)
		return (NULL);
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
