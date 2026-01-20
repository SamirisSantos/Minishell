/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:04:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/01/20 16:21:53 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	ft_printf(1, "^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigint_clear(t_shell *shell, char *input)
{
	shell->exit_status = EXIT_SIGINT;
	g_sig = 0;
	if (input)
		free(input);
}
