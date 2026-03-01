/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:17:48 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/24 11:18:06 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_heredoc_sig(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	heredoc_sig_exit(t_shell *shell, char *line)
{
	shell->exit_status = EXIT_SIGINT;
	g_sig = 0;
	if (line)
		free(line);
}
