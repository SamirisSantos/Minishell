/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/23 17:16:12 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errors.h"
# include "structs.h"

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
void	init_data(&shell, envp);

//tokens
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **list, t_token *new);
void	free_tokens(t_token *list);

//getting tokens
t_token_type	get_token_type(char *s);
char			*get_quoted_word(char **s);
char			*get_word(char **s);
char			*get_operator(char **s);

//lexer
t_token	*lexer(char *input);

//parser
t_cmd	*parse_tokens(t_token *tokens);
int		syntax_check(t_token *tokens);

//signals

//utils

#endif