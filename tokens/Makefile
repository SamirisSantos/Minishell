#  APAGAR | DEL
# =====================================
#.           MAKEFILE TESTE
# =====================================

NAME = test_extractor

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I../headers

TEST_MAIN = teste_tokens.c

SRCS = $(TEST_MAIN) \
		extract.c \
		utils_tokens.c \
		ft_substr.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_memcpy.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re