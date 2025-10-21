# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpinho-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 14:05:01 by cpinho-c          #+#    #+#              #
#    Updated: 2024/10/31 14:07:07 by cpinho-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
AR = ar rcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	   ft_memmove.c ft_memset.c ft_strchr.c ft_strlcpy.c ft_strlen.c \
	   ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
	   ft_strlcat.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_itoa.c ft_split.c ft_strmapi.c ft_striteri.c \
	   ft_printf/ft_printf.c ft_printf/printf_char.c ft_printf/printf_digits.c \
	   ft_printf/printf_hex.c ft_printf/printf_ptr.c ft_printf/printf_str.c \
	   ft_printf/printf_uns.c gnl/get_next_line.c gnl/get_next_line_utils.c
	
OBJS = $(SRCS:.c=.o)
RM = rm -rf

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
