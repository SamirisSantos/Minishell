/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:29 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/25 15:39:23 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>

typedef enum e_token_type
{
	CMD,				// comandos
	CMD_ARG,			// words
	PIPE,				// |
	REDIR_IN,			// <
	REDIR_IN_FILE,		// Name infile
	REDIR_OUT,			// >
	REDIR_OUT_FILE,		// Name outfile
	APPEND,				// >>
	HEREDOC,			// <<
	DELIMITER,			// Delimitador do Heredoc
	SPACE_TOKEN
}			t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
}			t_token;

typedef struct s_redir
{
	char			*filename;
	t_token_type	type;
	struct s_redir	*next;
}			t_redir;

typedef struct s_tree
{
	char			*data;
	char			**cmd_args;
	char			*heredoc_eof;
	t_token_type	type;
	t_redir			*redir;
	struct s_tree	*left;
	struct s_tree	*right;
}			t_tree;

typedef struct s_xcmd
{
	int		**pipe_fd;
	int		cmd_count;
	char	**cmd_path;
	pid_t	*pids;
}			t_xcmd;

typedef struct s_shell
{
	char	*orig_input; //DEBUG
	char	**envp_cpy;
	char	*cwd;
	int		exit_status;
	int		heredoc_count;
	t_xcmd	*xcmd;
	t_token	*token;
	t_tree	*tree;
}			t_shell;

#endif