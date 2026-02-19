#!/bin/bash

# --- Cores e Estilos ---
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
CYAN="\033[0;36m"
RESET="\033[0m"
BOLD="\033[1m"
BG_BLUE="\033[1;37;44m"

# --- Contadores e Configurações ---
TOTAL=0
PASSED=0
FAILED=0
TMP_OUT="/tmp/minishell_out.txt"

# --- Funções Auxiliares ---

print_header() {
    echo -e "\n${BG_BLUE}  $1  ${RESET}"
}

# run_test "Nome" "Comandos" "Esperado" "Modo"
# Modos: grep (padrão), status (verifica exit code), exact (match total)
run_test() {
	local label=$1
	local cmds=$2
	local expected=$3
	local mode=${4:-"grep"}
	((TOTAL++))

	echo -e "$cmds\nexit" | timeout 2 ./minishell > "$TMP_OUT" 2>&1
	local ret=$?
	local success=0
	case $mode in
		"grep")
			grep -q "$expected" "$TMP_OUT" && success=1 ;;
		"status")
			[ $ret -eq "$expected" ] && success=1 ;;
		"exact")
			[ "$(cat $TMP_OUT | tr -d '\n')" == "$expected" ] && success=1 ;;
	esac
	if [ $success -eq 1 ]; then
		printf "  %-35s ===> [%bOK%b]\n" "$label" "${GREEN}${BOLD}" "${RESET}"
		((PASSED++))
	else
		printf "  %-35s ===> [%bKO%b]\n" "$label" "${RED}${BOLD}" "${RESET}"
		((FAILED++))
	fi
}

# --- Início do Script ---
clear
echo -e "${CYAN}${BOLD}TESTER MINISHELL${RESET}"
echo "----------------------------------------------"
echo -e "Início: $(date +"%d %B %Y %R")"
echo "----------------------------------------------"

# 1. Verificação de Compilação
print_header "1. MAKEFILE"
make > /dev/null 2>&1
if [ $? -eq 0 ] && [ -f "./minishell" ]; then
	echo -e "  Compilação                   ===> ${GREEN}${BOLD}OK!${RESET}"
else
	echo -e "  Compilação                   ===> ${RED}${BOLD}KO!${RESET}"
	exit 1
fi

# 2. Comandos Simples
print_header "2. COMANDOS SIMPLES"
run_test "Echo hello" "echo hello" "hello"
run_test "PWD" "pwd" "/"
run_test "Env" "env" "PATH="

# 3. Builtin Echo
print_header "3. BUILTIN ECHO"
run_test "Echo -n" "echo -n hello" "hello"
run_test "Echo com aspas duplas" 'echo "42 Porto"' "42 Porto"
run_test "Echo com aspas simples" "echo '42 Lisboa'" "42 Lisboa"

# 4. Expansão de Variáveis
print_header "4. EXPANSÃO"
run_test "Variável \$USER" "echo \$USER" "$USER"
run_test "Variável \$?" "echo \$?" "[0-9]+" "grep"
run_test "Variável inexistente" "echo \$VAR_QUE_NAO_EXISTE" "" "exact"

# 5. Redirecionamentos
print_header "5. REDIRECIONAMENTOS"
echo "conteudo de teste" > /tmp/test_in.txt
run_test "Input <" "cat < /tmp/test_in.txt" "conteudo de teste"
run_test "Output >" "echo redir_test > /tmp/test_out.txt" "" "status"
run_test "Append >>" "echo linha2 >> /tmp/test_out.txt" "" "status"

# 6. Pipes
print_header "6. PIPES"
run_test "Pipe simples (ls | grep)" "ls | grep minishell" "minishell"
run_test "Múltiplos pipes" "echo hello | cat | cat | cat" "hello"

# 7. Heredoc
print_header "7. HEREDOC"
run_test "Heredoc básico" "cat << EOF\nola mundo\nEOF" "ola mundo"
run_test "Heredoc com expansão" "cat << LIMIT\n\$USER\nLIMIT" "$USER"

# 8. Sintaxe Inválida (Devem falhar/dar erro)
print_header "8. SINTAXE INVÁLIDA"
run_test "Pipe no início" "| ls" "" "status"
run_test "Redirecionamento vazio" "cat <" "" "status"
run_test "Token duplo (>> >)" "echo > >" "" "status"
run_test "Aspas não fechadas" "echo \"hello" "" "status"

# 9. Valgrind (opcional)
if command -v valgrind &> /dev/null; then
	print_header "9. MEMORY LEAKS"
	echo "exit" | valgrind --leak-check=full --error-exitcode=1 ./minishell &> /dev/null
	if [ $? -eq 0 ]; then
		echo -e "  Valgrind                     ===> ${GREEN}${BOLD}OK!${RESET}"
	else
		echo -e "  Valgrind                     ===> ${RED}${BOLD}KO!${RESET}"
	fi
fi

# --- Resumo Final ---
echo -e "\n${CYAN}╔════════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║                  ${BOLD}RESUMO FINAL${RESET}${CYAN}                   ║${RESET}"
echo -e "${CYAN}╚════════════════════════════════════════════════════╝${RESET}"
echo -e "  Total de testes: $TOTAL"
echo -e "  ${GREEN}Passaram:        $PASSED${RESET}"
echo -e "  ${RED}Falharam:        $FAILED${RESET}"

if [ $TOTAL -gt 0 ]; then
	PERCENTAGE=$((PASSED * 100 / TOTAL))
	echo -e "  Taxa de sucesso: ${PERCENTAGE}%"
fi

# Cleanup
rm -f /tmp/test_in.txt /tmp/test_out.txt "$TMP_OUT"

if [ $FAILED -eq 0 ]; then
	echo -e "\n${GREEN}${BOLD}🎉 EXCELENTE TRABALHO! 🎉${RESET}\n"
	exit 0
else
	echo -e "\n${RED}${BOLD}⚠️  VOCÊ TEM $FAILED FALHA(S) PARA CORRIGIR.${RESET}\n"
	exit 1
fi