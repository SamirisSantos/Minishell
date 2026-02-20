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

void	handle_heredoc(t_shell *shell, t_tree *tree, t_token **tokens)
{
	char	*num;
	char	*filename;
	int		fd;

	shell->heredoc_count++;
	num = ft_itoa(shell->heredoc_count);
	tree->fd_in_type = (*tokens)->type;
	filename = ft_strjoin(".heredoc_temp_", num);
	free(num);
	fd = open_heredoc(shell, filename);
	*tokens = (*tokens)->next;
	fill_heredoc(shell, &fd, (*tokens)->data);
	*tokens = (*tokens)->next;
	tree->fd_in = ft_redir_in(shell, filename);
	tree->heredoc_name = filename;
}
