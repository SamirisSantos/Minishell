/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/21 13:38:47 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h> //allows use of errno for system error msgs
# include <string.h> //strerror to get char * with errno msg
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

# include "structs.h"

# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131


//controle shell chamar todo as funções de depois chamar na main
void	shell_control(t_shell *shell);

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
void	free_cmd(t_cmd *cmd);

//inits
t_shell	*init_shell(void);
t_tree	*init_tree_node(t_shell *shell);
void	init_pipes(t_shell *shell);
void	init_pid(t_shell *shell);
void	init_signals(void);
void	init_cmd_path(t_shell *shell);
void	init_xcmd(t_shell *shell);
t_cmd	*init_cmd(void);

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
t_token	*handle_operator(char **input, t_token **head);
t_token	*handle_word(char **input, t_token **head, t_token *last_token);

//remove_quotes
void	quote_flag(char c, char *quote_char);
char	*remove_quotes(char *str);
int		unclosed_quotes(char *input);

//expansion
void	expand_tokens(t_token *token_list, t_shell *shell);
int		get_expanded_len(char *str, t_shell *shell);
void	fill_expanded_str(char *new_str, char *old_str, t_shell *shell);

//parser
t_cmd	*init_cmd(void);
t_cmd	*parse_tokens(t_token *tokens);
int		is_syntax_valid(t_token *tokens);
t_cmd	*parse_tokens(t_token *tokens);
t_token	*handle_redirects(t_token *token, t_cmd *cmd);

//signals


//tree
t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left);
t_tree	*build_node(t_shell *shell, t_token *tokens);
char	**build_args(t_token **tokens);
int		ft_redir_in(t_shell *shell, char *filename);
int		ft_redir_out(t_shell *shell, char *filename, t_token_type type);
void	check_redir(t_shell *shell, t_tree *tree, t_token **token);

//utils
char	**copy_envp(t_shell *shell, char *envp[]);
char	**ft_realloc_envp(char **envp, size_t old_size);
size_t	ft_find_var_name(char *arg);

#endif