/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:31:13 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/18 22:25:22 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return (NULL);
	}
	shell->cwd = NULL;
	shell->envp_cpy = NULL;
	shell->exit_status = 0;
	shell->heredoc_count = 0;
	shell->orig_input = NULL;
	shell->cmd = NULL;
	shell->xcmd = NULL;
	shell->token = NULL;
	shell->tree = NULL;
	return (shell);
}
