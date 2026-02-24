/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/23 10:37:34 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*expand_string(char *str, t_shell *shell)
{
	char	*new_str;
	int		final_len;

	if (!str)
		return (NULL);
	final_len = get_expanded_len(str, shell);
	new_str = (char *)malloc(sizeof(char) * (final_len + 1));
	if (!new_str)
		return (NULL);
	fill_expanded_str(new_str, str, shell);
	return (new_str);
}

static void	process_token(t_token *current, t_token *prev, t_shell *shell)
{
	char	*expanded_data;
	char	*clean_delim;

	if (prev && prev->type == HEREDOC)
	{
		clean_delim = remove_quotes(current->data);
		if (clean_delim)
		{
			free(current->data);
			current->data = clean_delim;
		}
	}
	else if (current->type == CMD || current->type == CMD_ARG
		|| current->type == REDIR_IN_FILE || current->type == REDIR_OUT_FILE)
	{
		expanded_data = expand_string(current->data, shell);
		if (expanded_data)
		{
			free(current->data);
			current->data = expanded_data;
		}
	}
}

void	expand_tokens(t_token *token_list, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = token_list;
	prev = NULL;
	while (current)
	{
		process_token(current, prev, shell);
		prev = current;
		current = current->next;
	}
}
