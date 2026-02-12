/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:04:11 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/12 15:52:47 by sade-ara         ###   ########.fr       */
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
	free_all(shell, input);
}
