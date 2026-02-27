/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:57:57 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:39:34 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_heredoc(t_shell *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		shell->exit_status = 1;
		ft_printf(STDERR_FILENO, "%s", strerror(errno));
	}
	return (fd);
}

void	fill_heredoc(t_shell *shell, int *fd, char *eof)
{
	char	*line;

	signal(SIGINT, handle_heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			heredoc_sig_exit(shell, line);
			break ;
		}
		if (!line)
			break ;
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0
			&& ft_strlen(line) == ft_strlen(eof))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, *fd);
		free(line);
	}
	close(*fd);
}

int	handle_heredoc(t_shell *shell, char *filename, char *eof)
{
	int		fd;

	fd = open_heredoc(shell, filename);
	fill_heredoc(shell, &fd, eof);
	return (fd);
}

char	*get_heredoc_info(t_shell *shell, t_tree *tree, t_token **token)
{
	char	*num;
	char	*filename;

	shell->heredoc_count++;
	num = ft_itoa(shell->heredoc_count);
	filename = ft_strjoin(".heredoc_temp_", num);
	free(num);
	(*token) = (*token)->next;
	if ((*token)->type == DELIMITER)
	{
		tree->heredoc_eof = ft_strdup((*token)->data);
		handle_heredoc(shell, filename, tree->heredoc_eof);
		(*token) = (*token)->next;
	}
	return (filename);
}
