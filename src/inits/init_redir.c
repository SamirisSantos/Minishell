/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:14:39 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/24 15:12:17 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_redir	*init_redir(t_shell *shell)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return (NULL);
	}
	redir->type = 0;
	redir->filename = NULL;
	redir->next = NULL;
	return (redir);
}
