/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:29 by sade-ara          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/10/13 15:50:01 by sade-ara         ###   ########.fr       */
=======
/*   Updated: 2025/10/28 16:22:36 by cpinho-c         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_shell
{
	char	*orig_input; //DEBUG
	char	**envp_cpy;
	char	*cwd;
	int		exit_status;
	t_token	*token;
	t_tree	*tree;
}	t_shell;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef enum s_token_type
{
<<<<<<< Updated upstream
	CMD,
	CMD_ARG,
	PIPE,
	REDIR_IN,
	REDIR_IN_FILE,
	REDIR_OUT,
	REDIR_OUT_FILE,
	APPEND,
	HEREDOC,
=======
	char	**args;			// lista de argumentos
	char	*input_file;	// <
	char	*output_file;	// >
	int		append;			// >>
	int		heredoc;		// <<
	struct s_cmd *next;		// pipes
}		t_cmd;

typedef enum e_token_type
{
	CMD,               // comandos
	CMD_ARG,           // words
	PIPE,              // | 
	REDIR_IN,          // <
	REDIR_IN_FILE,     // Name infile
	REDIR_OUT,         // >
	REDIR_OUT_FILE,    // Name outfile
	APPEND,            // >>
	HEREDOC,           // <<
>>>>>>> Stashed changes
	SPACE_TOKEN
}	t_token_type;

typedef struct s_tree
{
	char			*data;
	char			**cmd_args;
	t_token_type	type;
	bool			redir_in;
	bool			redir_out;
	int				fd_in;
	int				fd_out;
	t_tree			*left;
	t_tree			*right;
}	t_tree;

#endif