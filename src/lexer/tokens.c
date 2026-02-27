/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:56:33 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/25 11:41:19 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->data = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*current;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
