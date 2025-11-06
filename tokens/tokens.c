/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:56:33 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/06 16:11:30 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
Como funciona a leitura de uma linha de comando

cat file.txt | grep "error" > out.txt

t_comd 1:
  args: ["cat", "file.txt"]
  outfile_file: NULL
  next → t_command 2

t_comd 2:
  args: ["grep", "error"]
  outfile_file: "out.txt"
  append: 0
*/


// criar um novo token
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
// Adiciona token ao fim da lista
void	add_token(t_token **list, t_token *new)
{
	t_token	*current;

	if (!list || !new)
		return;
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

//Liberta memória da lista
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
