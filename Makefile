# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/03 16:00:55 by sade-ara          #+#    #+#              #
#    Updated: 2025/11/11 11:19:09 by cpinho-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
SRCS = main.c \

		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_pwd \
		builtins/ft_unset \

		executor/

		inits/init_shell.c \
		inits/init_tree.c \

		parser/parser.c \

		signals/signals.c \

		tree/binary_tree.c \
		tree/tree_utils.c \

		utils/ft_envp_utils.c \
		utils/ft_envp.c \
		utils/utils.c \

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