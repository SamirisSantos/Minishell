/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:55 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 14:39:59 by sade-ara         ###   ########.fr       */
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
			if (is_input_valid(input, shell) != 0 )
				continue ;
			tokens = lexer(input);
			if (is_syntax_valid(tokens) != 0)
			{
				shell->exit_status = 2;
				free_tokens(tokens);
				free(input);
				continue ;
			}
			cmd = parse_tokens(tokens);
			execute(cmd); //TODO
			free_all(tokens, cmds, input);
		}
}
