/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:31:13 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/19 14:21:02 by sade-ara         ###   ########.fr       */
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
