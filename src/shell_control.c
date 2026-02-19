/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 13:38:10 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	is_input_valid(char * input, t_shell *shell)
{
	if (!input)
		return (1);
	if (*input == '\0')
	{
		free_all(shell, input);
		return (1);
	}
	add_history(input);
	return (0);
}

void	shell_control(t_shell *shell, char *input)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
	while(1)
		{
			input = readline("minishell$");
			if (g_sig == SIGINT)
				sigint_clear(shell, input);
			if (!input)
				break;
			if (is_input_valid(input, shell) != 0 )
			{
				free(input);
				continue ;
			}
			shell->token = lexer(input);
			if (is_syntax_valid(shell->token) != 0)
			{
				shell->exit_status = 2;
				free_tokens(shell->token);
				free(input);
				continue ;
			}
			//cmd = parse_tokens(shell->token);
			pre_executor(shell);
			// free_all(shell, input);
		}
}

