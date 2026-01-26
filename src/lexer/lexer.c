/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:29:34 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/26 13:51:43 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
APAGAR | DEL
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

// criar lista de tokens
/*
APAGAR | DEL
Le a linha de comando
 -> se tiver espaco em branco no inicio ignorar.
 -> verificar se 'e um operador
 -> verificar se 'e um comando
 -> verificar se 'e um palavra
 -> verificar infile e outfile
 -> verificar pipe
*/

static t_token	*next_token(char **input, t_token **head, t_token *last_token)
{
	t_token	*new;

	new = NULL;
	if (is_metachar(**input))
		new = handle_operator(input, head);
	else
		new = handle_word(input, head, last_token);
	return (new);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*last_token;
	t_token	*new;

	head = NULL;
	new = NULL;
	last_token = NULL;
	while (*input)
	{
		while (*input && is_space(*input))
			input++;
		if (!*input)
			break ;
		new = next_token(&input, &head, last_token);
		if (!new)
		{
			free_tokens(head);
			return (NULL);
		}
		last_token = new;
	}
	return (head);
}
