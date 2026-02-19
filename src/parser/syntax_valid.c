/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:13 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/28 17:12:37 by sade-ara         ###   ########.fr       */
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
	return (type == CMD || type == CMD_ARG || 
			type == REDIR_IN_FILE || type == REDIR_OUT_FILE || 
			type == DELIMITER);
}

int	is_syntax_valid(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (msg_error("|"));
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!tokens->next || tokens->next->type == PIPE)
				return (msg_error("|"));
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT ||
				 tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next)
				return (msg_error("newline"));
			if (!is_valid_file(tokens->next->type))
				return (msg_error(tokens->next->data));
		}
		tokens = tokens->next;
	}
	return (1);
}
