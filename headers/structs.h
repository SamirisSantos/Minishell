/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:29 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/23 15:27:03 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"
# include <stdbool.h>

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

typedef struct  s_cmd
{
	char	**args; // lista de argumentos
	char	*input_file; // <
	char	*output_file; // >
	int		append; // >>
	int		heredoc; // <<
	struct s_cmd *next; // pipes
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