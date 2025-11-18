/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:29 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/18 19:40:37 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>

//changed to fix order of declaration to avoid something needing
//something that was not yet declared

typedef struct s_cmd
{
	char			**args;			// lista de argumentos
	char			*input_file;	// <
	char			*output_file;	// >
	int				append;			// >>
	int				heredoc;		// <<
	struct s_cmd	*next;			// pipes
}			t_cmd;

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
	SPACE_TOKEN
}			t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	t_token			*next;
}			t_token;

typedef struct s_tree
{
	char			*data;
	char			**cmd_args;
	t_token_type	type;
	t_token_type	fd_in_type;
	t_token_type	fd_out_type;
	int				fd_in;
	int				fd_out;
	t_tree			*left;
	t_tree			*right;
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
	t_xcmd	*xcmd;
	t_token	*token;
	t_tree	*tree;
}			t_shell;

#endif