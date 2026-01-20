# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/03 16:00:55 by sade-ara          #+#    #+#              #
#    Updated: 2026/01/20 16:31:08 by cpinho-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
SRCS = main.c \

		src/builtins/ft_cd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_export.c \
		src/builtins/ft_pwd \
		src/builtins/ft_unset \

		src/executor/builtin_exec.c \
		src/executor/cmd_path.c \
		src/executor/executor.c \

		src/expander/expancion.c \
		src/expander/remove_quotes.c \
		src/expander/utils_expansion.c \

		src/free/clear_heredoc.c \
		src/free/close_pipes.c \
		src/free/free_all.c \
		src/free/free_array.c \
		src/free/free_cmd.c \
		src/free/free_pipe_pids.c \
		src/free/free_shell.c \
		src/free/free_token.c \
		src/free/free_tree.c \

		src/heredoc/heredoc_main.c \

		src/inits/init_cmd.c \
		src/inits/init_exec.c \
		src/inits/init_shell.c \
		src/inits/init_tree.c \

		src/lexer/extract_word.c \
		src/lexer/handle_tokens.c \
		src/lexer/lexer.c \
		src/lexer/tokens.c \
		src/lexer/utils_tokens.c \

		src/parser/parser.c \
		src/parser/syntax_valid.c \
		src/parser/unclosed_quotes.c \

		src/tree/binary_tree.c \
		src/tree/tree_utils.c \

		src/utils/ft_envp_utils.c \
		src/utils/ft_envp.c \
		src/utils/handle_signals.c \

		src/shell_cibtrik \

		main.c

OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT = libft/libft.a

#VALGRIND
VALGRIND_FLAGS = --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp


.Silent:

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: all
	valgrind $(VALGRIND_FLAGS) $(VALGRIND_SUPP) ./$(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean

re: fclean all