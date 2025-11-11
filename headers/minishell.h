/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/11 17:00:36 by cpinho-c         ###   ########.fr       */
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
# include <readline/readline.h> // rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h> // add_history, rl_clear_history

# include "errors.h"
# include "structs.h"

//builtins
	//echo
void	ft_echo(t_shell *shell, t_tree *tree);
	//cd
void	update_pwd(t_shell *shell, char *newpath);
void	ft_cd(t_shell *shell, char *path);
	//pwd
void	ft_pwd(t_shell *shell, t_tree *tree);
	//exit
void	ft_exit(t_shell *shell);
	//export
void	ft_update_envp(t_shell *shell, int i, char *arg);
void	ft_add_var(t_shell *shell, char *arg);
bool	check_var_exists(t_shell *shell, char *cmd_arg, size_t size, int j);
void	ft_export(t_shell *shell, char **cmd_args);
	//unset
void	ft_fix_envp(t_shell *shell, int j);
void	ft_unset(t_shell *shell, char **cmd_args);

//executor

//free
void	free_array(char **array);
void	free_pipe_pids(t_shell *shell);
void	free_tree(t_tree *tree);
void	free_token(t_token *token);
void	free_shell(t_shell *shell);

//inits
t_shell	*init_shell(void);
t_tree	*init_tree_node(t_shell *shell);
void	init_pipes(t_shell *shell);
void	init_pid(t_shell *shell);

//parser

//signals

//tree
t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left);
t_tree	*build_node(t_shell *shell, t_token *tokens);
char	**build_args(t_token **tokens);
int		ft_redir(t_shell *shell, char *filename, t_token_type type);
void	check_redir(t_shell *shell, t_tree *tree, t_token **token);

//utils
char	**copy_envp(t_shell *shell, char *envp[]);
char	**ft_realloc_envp(char **envp, size_t old_size);
size_t	ft_find_var_name(char *arg);

#endif