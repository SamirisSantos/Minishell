/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:13 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/26 10:34:46 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	msg_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
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
		else if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
		{
			if (!tokens->next)
				return (msg_error("newline"));
			if (tokens->next->type == PIPE || 
				(tokens->next->type >= REDIR_IN && tokens->next->type <= HEREDOC))
				return (print_syntax_error(tokens->next->data));
		}
		tokens = tokens->next;
	}
	return (0);
}
