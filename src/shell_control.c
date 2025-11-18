/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/18 12:49:48 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
APAGAR | DEL
readline() → lexer(tokenrização) → parser → executor
1. readline()
2. VALIDAÇÃO DE SINTAXE (PRÉ-LEXER)
3. LEXER
4. EXTRACT_WORD
5. EXPANSION
6. PARSER
7. BUILD
8. EXECUTOR
9. LIMPEZA
*/

/*
APAGAR | DEL
* Lê a entrada, processa e executa.
* Esta funções separadas da main para cumprir a Norminette. kry
*/

static void	free_all(t_token tokens, t_cmd cmd, char *input)
{
	if (token)
		free_tokens;
	if (cmds)
		free_tree((t_tree *)cmds);
	if (input)
		free(input);
}

static int	check_input(char * input, t_shell *shell)
{
	if (!input)
		return (0);
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	add_history(input); // APAGAR | DEL biblioteca readline
	if (unclosed_quotes(input))
	{
		shell->exit_status = 2;
		free(input);
		return (0);
	}
	return (1);
}


void	shell_control(t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;
	char	*input;

	while(1)
		{
			input = readline("minishell$");
			if (!input)
				break;
			if (!check_input(input, shell))
				continue ;
			tokens = lexer(input);
			if (!syntax_check(tokens)) // TODO
			{
				shell->exit_status = 2;
				free_tokens(tokens);
				free(input);
				continue ;
			}
			cmds = parse_tokens(tokens); //TODO
			execute(cmds); //TODO
			free_all(tokens, cmds, input);
		}
}
