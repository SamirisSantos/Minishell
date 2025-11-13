/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:09:59 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/13 18:01:37 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//APAGAR | DELL APAGAR COMENTARIOS
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

void	quote_flag(char c, char *quote_char)
{
	if (*quote_char == 0 && (c == '\'' || c == '"'))
		*quote_char = c;
	else if (*quote_char != 0 && c == *quote_char)
			*quote_char = 0;
}


// Retorna 0 (SUCESSO) se as aspas estiverem fechadas.
// Retorna 1 (ERRO) se as aspas NÃO estiverem fechadas.
int	unclosed_quotes(char *input)
{
	char	quote_char;
	t_shell	*shell;

	quote_char = 0;
	while(*input)
	{
		quote_flag(*input, &quote_char);
		input++;
	}
	if (quote_char != 0)
	{
		printf("Não fechou a aspas"); //APAGAR | DELL
		shell->exit_status = 2;
		//TODO imprimir o erro de sintaxe
		return (1);
	}
	return (0);
}
