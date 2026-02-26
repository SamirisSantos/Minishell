/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:32:12 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/26 17:32:12 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_cmd_path(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->xcmd->cmd_count)
	{
		if (shell->xcmd->cmd_path[i])
			free(shell->xcmd->cmd_path[i]);
		i++;
	}
	free(shell->xcmd->cmd_path);
	shell->xcmd->cmd_path = NULL;
}