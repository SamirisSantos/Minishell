# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/03 16:00:55 by sade-ara          #+#    #+#              #
#    Updated: 2025/10/03 16:00:56 by sade-ara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
SRCS = 
OBJS = $(SRCS:.c=.o)
RM = rm -f

#VALGRIND
VALGRIND_FLAGS = --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp


.Silent:

all: $(NAME)

$(NAME): $(OBJS) 
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