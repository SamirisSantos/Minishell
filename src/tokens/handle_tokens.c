/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:54:21 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/07 13:37:50 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_token_type	get_operator_type(char *input, int *len)
{
	*len = 1;
	if (*input == '|')
		return (PIPE);
	else if (*input == '<')
	{
		if (*(input + 1) == '<')
		{
			*len = 2;
			return (HEREDOC);
		}
		return (REDIR_IN);
	}
	else if (*input == '>')
	{
		if (*(input + 1) == '>')
		{
			*len = 2;
			return (APPEND);
		}
		return (REDIR_OUT);
	}
	return (0);
}

t_token	*handle_operador(char **input, t_token **head)
{
	int				len;
	char			*value;
	t_token			*new_node;
	t_token_type	type;

	len = 0;
	type = get_operator_type(*input, &len);
	printf("valor de len no handler operdor depois do get%d", len);
	value = ft_substr(*input, 0, len);
	if (!value)
		return (NULL);
	new_node = new_token(value, type);
	if (!new_token_node)
	{
		free(value);
		return (NULL);
	}
	add_token(head, new_node);
	*input +=len;
	return (new_node);
}

/*
APAGAR | DEL
logica:
Se o ultimo token é uma PIPE o shell espera um comando 
ou a primeira entrada deve ser um comando, se nao tem
token operador e o primeira palavra no shel é um comando
exemplo:
cd NAME_FILE
echo hello
cat qualquer coisa
se não for nada tbm diz que o comando nao foi encontrado
----

Operadores de entrada < e <<

Exemplo             |   Antes    |   Depois
wc -l < dados.csv.  |   comando  | ARQUIVO
cat << FIM.         |   comando. | chave delimitadora

Operadores de saida  > e >>

Exemplo                   |   Antes    |   Depois
wc -l > dados.txt         |   comando  |  ARQUIVO
echo "fim" >>  file.txt   |   comando  |  ARQUIVO

*/

static 	t_token_type	get_word_type(t_token *last_token)
{
	if (!last_token || last_token == PIPE)
		return(CMD);
	if (last_token->type == REDIR_IN)
		return (REDIR_IN_FILE);
	if (last_token->type == REDIR_OUT || last_token->type == APPEND)
		return (REDIR_OUT_FILE);
	// CHAVE DELIMIDORA é uma argumento que deve ser expandido
	if (last_token == HEREDOC)
		return (CMD_ARG);
	return (CMD_ARG);
}

t_token	*handle_word(char **input, t_token **head, t_token *last_token)
{
	char			*value;
	t_token			*new_node;
	t_token_type	type;

	value = extract_word(input);
	if (!value)
		return (NULL);
	
	type = get_word_type(last_token);
	new_node = new_token(value, type);
	if (!new_node)
	{
		free(value);
		return (NULL);
	}
	add_token(head, new_token_node);
	return (new_token_node);
}
