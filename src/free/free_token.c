/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:39:44 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 13:40:14 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		if (token->data)
			free(token->data);
		free(token);
		token = temp;
	}
}
