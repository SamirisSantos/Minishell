/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/20 16:19:05 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_all(t_token tokens, t_cmd cmd, char *input)
{
	if (token)
		free_tokens;
	if (cmds)
		free_tree((t_tree *)cmds);
	if (input)
		free(input);
}

static int	is_input_valid(char * input, t_shell *shell)
{
	if (!input)
		return (1);
	if (*input == '\0')
	{
		free(input);
		return (1);
	}
	add_history(input);
	if (unclosed_quotes(input))
	{
		shell->exit_status = 2;
		free(input);
		return (1);
	}
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
			if (g_sig = SIGINT)
				sigint_clear(shell, input);
			if (!input)
				break;
			if (is_input_valid(input, shell) != 0 )
				continue ;
			shell->token = lexer(input);
			if (is_syntax_valid(shell->token) != 0)
			{
				shell->exit_status = 2;
				free_tokens(shell->token);
				free(input);
				continue ;
			}
			cmd = parse_tokens(shell->token); //doing ...
			build_tree(shell, shell->token, false);
			pre_executor(shell);
			free_all(shell, input);
		}
}
