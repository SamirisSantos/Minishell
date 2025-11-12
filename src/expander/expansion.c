/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/12 16:05:56 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*expand_string(char *str, char **envp)
{
	char	*new_str;
	int		final_len;

	if (!str)
		return (NULL);
	final_len = get_expanded_len(str, envp);
	new_str = (char *)malloc(sizeof(char) * (final_len + 1));
	if (!new_str)
		return (NULL);
	fill_expanded_str(new_str, str, envp);
	return (new_str);
}

void	expand_tokens(t_token *token_list, char **envp)
{
	t_token	*curr;
	t_token	*prev;
	char	*expanded_data;
	char	*clean_delim;

	curr = token_list;
	prev = NULL;
	while (curr)
	{
		if (prev && prev->type == HEREDOC)
		{
			*clean_delim = remove_quotes(curr->data);
			free(curr->data);
			curr->data = clean_delim;
		}
		else if (curr->type == CMD || curr->type == CMD_ARG
			|| curr->type == REDIR_IN_FILE || curr->type == REDIR_OUT_FILE)
		{
			*expanded_data = expand_string(curr->data, envp);
			free(curr->data);
			curr->data = expanded_data;
		}
		prev = curr;
		curr = curr->next;
	}
}
