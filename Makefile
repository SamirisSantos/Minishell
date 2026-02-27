# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/03 16:00:55 by sade-ara          #+#    #+#              #
#    Updated: 2026/02/19 18:08:46 by cpinho-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCS = main.c \
	src/builtins/ft_cd.c \
	src/builtins/ft_echo.c \
	src/builtins/ft_env.c \
	src/builtins/ft_exit.c \
	src/builtins/ft_export.c \
	src/builtins/ft_pwd.c \
	src/builtins/ft_unset.c \
	src/executor/builtin_exec.c \
	src/executor/check_cmd.c \
	src/executor/cmd_path.c \
	src/executor/pre_executor.c \
	src/executor/executor.c \
	src/executor/utils_exec.c \
	src/expander/expansion.c \
	src/expander/remove_quotes.c \
	src/expander/gets.c \
	src/expander/utils_expansion.c \
	src/free/close_pipes.c \
	src/free/free_array.c \
	src/free/free_pipe_pids.c \
	src/free/free_redir.c \
	src/free/free_shell.c \
	src/free/free_tokens.c \
	src/free/free_tree.c \
	src/heredoc/heredoc_main.c \
	src/heredoc/heredoc_signals.c \
	src/inits/init_exec.c \
	src/inits/init_pipes.c \
	src/inits/init_redir.c \
	src/inits/init_shell.c \
	src/inits/init_tree.c \
	src/lexer/extract_word.c \
	src/lexer/handle_tokens.c \
	src/lexer/lexer.c \
	src/lexer/tokens.c \
	src/lexer/utils_tokens.c \
	src/parser/syntax_valid.c \
	src/tree/binary_tree.c \
	src/tree/tree_utils.c \
	src/utils/ft_envp_utils.c \
	src/utils/ft_export_utils.c \
	src/utils/ft_envp.c \
	src/utils/handle_redir.c \
	src/utils/handle_signals.c \
	src/shell_control.c 

OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Valgrind
VALGRIND_FLAGS = --quiet --leak-check=full --show-leak-kinds=all \
				 --track-fds=yes --trace-children=yes --suppressions=readline.supp


# Colors
GREEN = \033[0;32m
RESET = \033[0m

.SILENT:


all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compilada$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ minishell compilado com sucesso!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: all
	@echo "$(YELLOW)Executando valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re valgrind