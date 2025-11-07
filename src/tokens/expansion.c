/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:09:59 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/07 16:29:13 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// SE str == '\0' nao chamar o remove_quotes
/*
Pegar a string do lexer, verificar se tem aspas e tira as aspas.
Procura a primeira aspas varre a string e encontra a segunda aspas.
e guarda a string sem aspas

exemplo:
teste de extract_wor
[1] Chamando extract_word em: ""e"cho name"
      -> Extraído (Palavra): ""e"cho"
      -> Ponteiro restante: " name"
[2] Chamando extract_word em: "name"
      -> Extraído (Palavra): "name"
      -> Ponteiro restante: ""
str = "ec"ho 
clean_str = echo
*/

/*
**  ------------------------------------------------------------------------------------------
**  | Entrada     | Saída (clean_str) | Bash faz? | Observação                    |
**  ------------------------------------------------------------------------------------------
**  | "ec"ho      | echo              | ✅ Sim    | Aspas fechadas corretamente  |
**  | 'ec"ho'     | ec"ho             | ✅ Sim    | ' protege "                  |
**  | "ec'ho"     | ec'ho             | ✅ Sim    | " não afeta '                |
**  | ec"ho       | echo              | ⚠️ Não    | Bash dá erro (aspa aberta)   |
**  | 'ec"ho      | ec"ho             | ⚠️ Não    | Bash dá erro (aspa aberta)   |
**  | "e'c"h'o    | e'cho             | ✅ Sim    | Aspas mistas válidas         |
**  ------------------------------------------------------------------------------------------
*/

static void	quote_flag(char c, char *quote_char)
{
	if (*quote_char == 0 && (c == '\'' || c == '"'))
		*quote_char = c;
	else if (*quote_char != 0 && c == *quote_char)
			*quote_char = 0;
}

static int	unclosed_quotes(char *input)
{
	
}

static char	*remove_quotes(char *str)
{
	char	*clean_str;
	char	*quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_char = 0; //FLAG
	clean_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!clean_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && 
			(quote_char == 0 || str[i] == quote_char))
			quote_flag(str[i++], &quote_char);
		else
			clean_str[j++] = str[i++];
	}
	clean_str[j] = '\0';
	return (clean_str);
}

void	expand_tokens(t_token *token_list, char **envp)
{
	
}

//APAGAR | DEL -> MAIN

/*
 * ==========================================================
 * MAIN DE TESTE
 * ==========================================================
 */

