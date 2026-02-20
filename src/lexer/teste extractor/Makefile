#  APAGAR | DEL
# =====================================
#.           MAKEFILE TESTE
# =====================================

NAME = test_extractor

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = ../../libft
LIBFT_A = $(LIBFT_PATH)/libft.a

MINISHELL_HEADERS = ../../headers
INCLUDES = -I$(MINISHELL_HEADERS) -I$(LIBFT_PATH)

LDFLAGS = -L$(LIBFT_PATH)
LDLIBS = -lft

TEST_MAIN = teste_tokens.c

SRCS = teste_tokens.c \
		extract_word.c \
		utils_tokens.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Ligando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo "$(NAME) pronto! (em ./tokens/)"

%.o: %.c
	@echo "Compilando $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@echo "Compilando a Libft em $(LIBFT_PATH)..."
	@$(MAKE) -s -C $(LIBFT_PATH)

clean:
	@$(MAKE) -s -C $(LIBFT_PATH) clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re