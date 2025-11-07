/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/07 15:20:23 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "../libft/libft.h"
# include "errors.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h> //bool variables
# include <limits.h> //adds variables to int MAX/MIN, PATH_MAX, etc
# include <sys/types.h> // pid_t, stat types
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, unlink
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <fcntl.h> // open
# include <dirent.h> // opendir, readdir, closedir
# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h> // add_history, rl_clear_history

//builtins

//executor

//inits
void	init_data(t_shell *shell, char **envp);

//tokens
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **list, t_token *new);
void	free_tokens(t_token *list);

//extract word and lexer
char	*extract_word(char **s);
t_token	*lexer(char *input);
int		is_metachar(char c);
int		is_space(char c);
int		is_quote(char c);
t_token	*handle_operador(char **input, t_token **head);
t_token	*handle_word(char **input, t_token **head, t_token *last_token);

//expansion
void	expand_tokens(t_token *token_list, char **envp);

//parser
t_cmd	*parse_tokens(t_token *tokens);
int		syntax_check(t_token *tokens);

//signals

//utils

#endif