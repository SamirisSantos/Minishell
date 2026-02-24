/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:06:54 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/24 11:08:54 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_redir_out(t_shell *shell, char *filename, t_token_type type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
	}
	return (fd);
}

int	ft_redir_in(t_shell *shell, char *filename)
{
	int	fd;

	fd = -1;
	if (access(filename, F_OK) == 0)
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n", filename, strerror(errno));
	}
	return (fd);
}