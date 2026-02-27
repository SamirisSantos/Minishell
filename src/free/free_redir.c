/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:03:36 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/26 17:56:22 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		temp = redir->next;
		if (redir->type == HEREDOC)
			unlink(redir->filename);
		free(redir->filename);
		free(redir);
		redir = temp;
	}
}
