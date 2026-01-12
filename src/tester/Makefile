## APAGAR | DELL

# ============================================================================
#  TESTER MAKEFILE
# ============================================================================

NAME        = test_minishell

# Compilador e Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# --- DIRETÓRIOS ---
ROOT_DIR    = ../..
SRC_DIR     = ..
LIBFT_DIR   = $(ROOT_DIR)/libft
HEADER_DIR  = $(ROOT_DIR)/headers

# --- BIBLIOTECAS ---
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(HEADER_DIR) -I$(LIBFT_DIR)
LIBS        = -L$(LIBFT_DIR) -lft -lreadline

# --- FONTES ---
# Aqui listamos os arquivos das outras pastas que precisamos compilar
# para o teste funcionar.

# 1. Lexer
LEXER_SRCS  = $(SRC_DIR)/lexer/lexer.c \
              $(SRC_DIR)/lexer/extract_word.c \
              $(SRC_DIR)/lexer/tokens.c \
              $(SRC_DIR)/lexer/handle_tokens.c \
              $(SRC_DIR)/lexer/utils_tokens.c

# 2. Parser
PARSER_SRCS = $(SRC_DIR)/parser/parser.c \
              $(SRC_DIR)/parser/syntax_check.c \
              $(SRC_DIR)/parser/unclosed_quotes.c

# 3. Expander
EXP_SRCS    = $(SRC_DIR)/expander/utils_expansion.c \
              $(SRC_DIR)/expander/expansion.c \
              $(SRC_DIR)/expander/remove_quotes.c

# 4. Utils / Free
UTILS_SRCS  = $(SRC_DIR)/free/free_tokens.c \
              $(SRC_DIR)/free/free_cmd.c

# 5. Inits
UTILS_SRCS  = $(SRC_DIR)/inits/inits_cmd.c

# 6. O arquivo main do teste
TEST_SRC    = tester_parsing.c

# Junta tudo
ALL_SRCS    = $(TEST_SRC) $(LEXER_SRCS) $(PARSER_SRCS) $(EXP_SRCS) $(UTILS_SRCS)

# Objetos
OBJS        = $(ALL_SRCS:.c=.o)

# --- REGRAS ---

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "🔗 Ligando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "✅ Teste pronto! Execute: ./$(NAME)"

# Regra genérica para compilar .c em .o (funciona para ../pasta/arquivo.c)
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Garante que a libft existe
$(LIBFT):
	@echo "📦 Compilando Libft..."
	@make -s -C $(LIBFT_DIR)

clean:
	@echo "🧹 Limpando objetos do teste..."
	@rm -f $(OBJS)

fclean: clean
	@echo "🗑️ Removendo executável..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re