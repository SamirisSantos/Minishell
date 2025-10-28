/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/10/03 16:15:35 by sade-ara         ###   ########.fr       */
=======
/*   Updated: 2025/10/28 18:53:19 by cpinho-c         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

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

# include "errors.h"
# include "structs.h"

//builtins

//executor

//inits

//parser

//signals

//tree
t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left);
char	**build_args(t_token **tokens);
int		ft_redir(t_shell *shell, char *filename, t_token_type type);
void	check_redir(t_shell *shell, t_tree *tree, t_token **token);

//utils

#endif