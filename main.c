/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/11 17:07:22 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "headers/minishell.h"

/*

readline() → lexer(tokenrização) → parser → executor

*/

int	g_exit_status = 0;

int main (int argc, char **argv, char *envp[])
{
	t_shell	*shell;
	int		shell_signal;
	t_cmd	*cmd;
	t_token	*tokens;
	char	*input;

	if (argc != 1)
	{
		perror("Error: too many arguments.");
		exit(0);
		// nao deve executar, pois primeiro deve entrar no shell
	}
	else
	{
		init_data(&shell, envp); //TODO
		while(1)
		{
			input = readline("minishell$");
			if (!input)
				break;
			if(shell_signal == EXIT_SIGINT)
				//TODO
			if (shell_signal == EXIT_SIGQUIT)
				/* TODO */
			tokens = lexer(input);
			if (syntax_check(tokens)) //TODO
				continue;
			cmds = parse_tokens(tokens); //TODO
			execute(cmds); //TODO
			free_all(tokens, cmds, input); //TODO
		}
	}
	return EXIT_SUCCESS;
}