/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:19:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/29 16:04:29 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_redir(t_shell *shell, t_tree *tree, t_token **token)
{
	if ((*token)->type == REDIR_IN_FILE)
	{
		tree->redir_in = true;
		tree->fd_in = ft_redir(shell, (*token)->data, (*token)->next->type);
		(*token) = (*token)->next->next;
	}
	if ((*token)->type == REDIR_OUT)
	{
		tree->redir_out = true;
		tree->fd_out = ft_redir(shell, (*token)->next->data, (*token)->type);
		(*token) = (*token)->next->next;
	}
}

int	ft_redir(t_shell *shell, char *filename, t_token_type type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_IN)
	{
		if (access(filename, F_OK))
			fd = open(filename, O_RDONLY);
		else
			ft_printf(STDERR_FILENO, "%s", ERROR_FILE_ACCESS);
	}
	else if (type == REDIR_OUT)
	{
		if (access(filename, F_OK) != 0)
			fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_printf(STDERR_FILENO, "%s", ERROR_FILE_PERMISSION);
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
	args = (char **)malloc((arg_count * sizeof(char *)) + 1);
	if (!args)
		return (NULL);
	i = 0;
	while ((*tokens) && (*tokens)->type == CMD_ARG)
	{
		args[i] = ft_strdup((*tokens)->data);
		(*tokens) = (*tokens)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
