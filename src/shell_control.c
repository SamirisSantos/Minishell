/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/20 11:23:03 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	process_input(t_shell *shell, char *input)
{
	shell->token = lexer(input);
	expand_tokens(shell->token, shell);
	if (is_syntax_valid(shell->token) == 1)
	{
		shell->tree = build_tree(shell, shell->token, false);
		if (shell->tree)
		{
			pre_executor(shell);
			free_tree(shell->tree);
			shell->tree = NULL;
		}
	}
	else
	{
		shell->exit_status = 2;
	}
	shell->token = NULL;
	free(input);
}

void	shell_control(t_shell *shell)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_sig = 0;
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf(1, "exit\n");
			free_shell(shell);
			break ;
		}
		if (*input == '\0' || g_sig == SIGINT)
		{
			free(input);
			continue ;
		}
		add_history(input);
		process_input(shell, input);
	}
}


