/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:13 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/20 15:08:49 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	msg_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	is_valid_file(t_token_type type)
{
	return (type == CMD || type == CMD_ARG
		|| type == REDIR_IN_FILE || type == REDIR_OUT_FILE
		|| type == DELIMITER);
}

int	is_syntax_valid(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (current->type == PIPE)
		return (msg_error("|"));
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next || current->next->type == PIPE)
				return (msg_error("|"));
		}
		else if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			if (!current->next)
				return (msg_error("newline"));
			if (!is_valid_file(current->next->type))
				return (msg_error(current->next->data));
		}
		current = current->next;
	}
	return (1);
}
