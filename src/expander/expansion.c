/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/25 16:07:38 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static int	process_token(t_token *current, t_token *prev, t_shell *shell)
{
	char	*new_str;
	int		had_quotes;

	had_quotes = has_quotes(current->data);
	if (prev && prev->type == HEREDOC)
		new_str = remove_quotes(current->data);
	else if (current->type == CMD || current->type == CMD_ARG
		|| current->type == REDIR_IN_FILE || current->type == REDIR_OUT_FILE)
		new_str = expand_string(current->data, shell);
	else
		return (0);
	if (!new_str)
		return (0);
	free(current->data);
	current->data = new_str;
	if (new_str[0] == '\0' && !had_quotes && (!prev || prev->type != HEREDOC))
		return (1);
	return (0);
}

static void	delete_token(t_token **list, t_token **curr, t_token *prev)
{
	t_token	*temp;

	temp = *curr;
	if (prev)
		prev->next = temp->next;
	else
		*list = temp->next;
	*curr = temp->next;
	free(temp->data);
	free(temp);
}

void	expand_tokens(t_token **token_list, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	prev = NULL;
	while (current)
	{
		if (process_token(current, prev, shell) == 1)
		{
			delete_token(token_list, &current, prev);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
