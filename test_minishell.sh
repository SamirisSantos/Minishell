#!/bin/bash

# Cores
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
CYAN="\033[0;36m"
MAGENTA="\033[0;35m"
RESET="\033[0m"
BOLD="\033[1m"
BG_BLUE="\033[1;37;44m"

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Funções auxiliares
print_header() {
	echo -e "\n${BG_BLUE}  $1  ${RESET}\n"
}

print_test() {
	echo -n "  $1 ... "
}

print_result() {
	if [ $1 -eq 0 ]; then
		echo -e "${GREEN}${BOLD}✓ PASS${RESET}"
		((PASSED_TESTS++))
	else
		echo -e "${RED}${BOLD}✗ FAIL${RESET}"
		((FAILED_TESTS++))
	fi
	((TOTAL_TESTS++))
}

run_test() {
	local test_name="$1"
	local test_cmd="$2"
	local expected_exit="$3"
	
	print_test "$test_name"
	
	# Executa o comando
	echo "$test_cmd" | timeout 2 ./minishell &> /tmp/minishell_output.txt
	local exit_code=$?
	
	# Verifica exit code se especificado
	if [ -n "$expected_exit" ]; then
		if [ $exit_code -eq $expected_exit ]; then
			print_result 0
		else
			print_result 1
			echo "    Expected exit: $expected_exit, Got: $exit_code"
		fi
	else
		print_result 0
	fi
}

# print intro
echo -e 
echo -e "TESTER MINISHELL"
echo "----------------------------------------------"
echo -e "Inicio do teste $(date +"%d %B %Y") $(date +%R)"
echo -e "by $USER on $os os"
echo "----------------------------------------------"

# ---------------------------
# 1. VERIFICAÇÃO DO MAKEFILE
# ---------------------------

print_header "1. MAKEFILE"

# executa o make
MAKE_OUTPUT=$(make 2>&1)
MAKE_EXIT_CODE=$?

if [ $MAKE_EXIT -ne 0 ]; then
	echo -e "${RED}${BOLD}✗ ERRO${RESET}"
	echo "$MAKE_OUTPUT"
	echo -e "\n${RED}${BOLD}TESTES CANCELADOS - Make falhou${RESET}\n"
	exit 1
else
	echo -e "${GREEN}${BOLD}✓ OK${RESET}"
fi

# Verifica se o executável foi criado
if [ ! -f "./minishell" ]; then
	echo -e "${RED}${BOLD}✗ ERRO: Executável minishell não foi criado${RESET}\n"
	exit 1
fi

# ------------------------------
# 2. VERIFICAÇÃO DA NORMINETTE
# ------------------------------

print_header "2. NORMINETTE"

NORMI_OUTPUT=$(find . -name "*.c" -o -name "*.h" | grep -v libft | xargs norminette 2>&1)

if echo "$NOMRI_OUTPUT" | grep -q "Error"; then
	echo -e "${RED}${BOLD}✗ ERROS ENCONTRADOS:${RESET}"
	echo "$NORM_OUTPUT" | grep "Error"
else
	echo -e "${GREEN}${BOLD}✓ Todos os arquivos passaram na norminette${RESET}"
fi

# ------------------------------
# 3. TESTES DE COMANDOS SIMPLES
# ------------------------------

print_header "3. COMANDOS SIMPLES"
