/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:35:11 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 13:36:22 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_shell(t_shell *shell)
{
	free(shell->cwd);
	free_array(shell->envp_cpy);
	free_pipe_pids(shell);
	free_tree(shell->tree);
	free_token(shell->token);
	free(shell);
}
