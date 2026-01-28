/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/28 17:42:29 by sade-ara         ###   ########.fr       */
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
			cmd = parse_tokens(shell->token); //doing ...
			build_tree(shell, shell->token, false);
			pre_executor(shell);
			free_all(shell, input);
		}
}
