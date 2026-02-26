/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:35 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:46:09 by cpinho-c         ###   ########.fr       */
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
# include <linux/limits.h>
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

extern int	g_sig;

//builtins
	//echo
void	ft_echo(t_shell *shell, t_tree *tree);
	//cd
void	exec_cd(t_shell *shell, t_tree *tree);
void	update_pwd(t_shell *shell, char *newpath);
void	ft_cd(t_shell *shell, char *path);
	//env
void	ft_env(t_shell *shell);
	//exit
void	ft_exit(t_shell *shell);
	//export
void	ft_update_envp(t_shell *shell, int i, char *arg);
void	ft_add_var(t_shell *shell, char *arg);
bool	check_var_exists(t_shell *shell, char *cmd_arg, size_t size, int j);
void	ft_export(t_shell *shell, char **cmd_args);
	//pwd
void	ft_pwd(t_shell *shell);
	//unset
void	ft_fix_envp(t_shell *shell, int j);
void	ft_unset(t_shell *shell, char **cmd_args);

//executor
	//builtin_exec
bool	is_builtin(t_tree *tree);
void	exec_builtin(t_shell *shell, t_tree *tree, bool is_child);
void	fork_builtin(t_shell *shell, t_tree *tree, int i);
	//check_cmd
int		check_cmd(t_shell *shell, t_tree *tree, int i);
	//cmd_path
void	count_cmds(t_tree *temp, int *cmd_count);
char	*find_cmd_path(t_shell *shell, t_tree *tree);
	//executor
void	close_parent_pipe(t_shell *shell, int i);
void	executor(t_shell *shell, t_tree *tree, int i);
int		check_cmd(t_shell *shell, t_tree *tree, int i);
void	start_exe(t_shell *shell, t_tree *tree, int *i);
void	pre_executor(t_shell *shell);
	//utils_exec
int		save_and_redirect(int *saved_stdin);
void	restore_fds(int saved_stdout, int saved_stdin);
void	execve_error(t_shell *shell, t_tree *tree);
void	apply_child_redirects(t_shell *shell, t_tree *tree);
int		apply_redirects(t_shell *shell, t_tree *tree);

//free
void	free_array(char **array);
void	close_pipes(t_shell *shell, int pipe_count);
void	free_pipe_pids(t_shell *shell);
void	free_pipe(t_shell *shell, int count);
void	free_tree(t_tree *tree);
void	free_tokens(t_token *list);
void	free_tokens(t_token *list);
void	free_shell(t_shell *shell);
void	free_cmd(t_cmd *cmd);
void	free_redir(t_redir *redir);

//heredoc
void	handle_heredoc_sig(int sig);
void	heredoc_sig_exit(t_shell *shell, char *line);
int		open_heredoc(t_shell *shell, char *filename);
int		open_heredoc(t_shell *shell, char *filename);
void	fill_heredoc(t_shell *shell, int *fd, char *eof);
int		handle_heredoc(t_shell *shell, char *filename, char *eof);
char	*get_heredoc_info(t_shell *shell, t_tree *tree, t_token **token);

//inits
t_shell	*init_shell(void);
t_tree	*init_tree_node(t_shell *shell);
void	init_pipes(t_shell *shell);
void	init_pid(t_shell *shell);
void	init_cmd_path(t_shell *shell);
void	init_xcmd(t_shell *shell);
t_cmd	*init_cmd(void);
t_redir	*init_redir(t_shell *shell);

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

//expansion
void	expand_tokens(t_token *token_list, t_shell *shell);
char	*get_env_value(char *name, char **envp);
char	*get_var_value(char *str, t_shell *shell, int *var_len);
int		get_expanded_len(char *str, t_shell *shell);
void	fill_expanded_str(char *new_str, char *old_str, t_shell *shell);
void	process_var_len(char *str, t_shell *shell, int *len, int *i);

//parser
int		is_syntax_valid(t_token *tokens);
t_cmd	*parse_tokens(t_token *tokens);
t_token	*handle_redirects(t_token *token, t_cmd *cmd);

//tree
t_tree	*build_tree(t_shell *shell, t_token *tokens, bool is_left);
t_tree	*build_node(t_shell *shell, t_token *tokens, t_tree *tree);
t_tree	*build_tree_pipe(t_shell *shell, t_tree *tree, t_token *tokens, t_token *pipe);
char	**build_args(t_shell *shell, t_token **tokens);
void	handle_cmd_no_args(t_shell *shell, t_tree *tree);
void	check_redir(t_shell *shell, t_tree *tree, t_token **token);
t_redir	*fill_redir(t_shell *shell, t_tree *tree, t_token **token);

//utils
int		ft_redir_in(t_shell *shell, char *filename);
int		ft_redir_out(t_shell *shell, char *filename, t_token_type type);
char	**copy_envp(t_shell *shell, char *envp[]);
char	**ft_realloc_envp(t_shell *shell, char **envp, size_t old_size);
size_t	ft_find_var_name(char *arg);

//signal
void	handle_sigint(int sig);
void	sigint_clear(t_shell *shell, char *input);

//main control
void	shell_control(t_shell *shell);

#endif