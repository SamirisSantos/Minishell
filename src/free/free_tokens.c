/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:39:44 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 16:11:41 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tokens(t_token *list)
{
	t_token	*current;
	t_token	*next_node;

	current = list;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->data)
		{
			free(current->data);
			current->data = NULL;
		}
		free(current);
		current = next_node;
	}
}
