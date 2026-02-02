#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
YEL="\033[0;33m"
RESET="\033[0m"
BOLD="\033[1m"
BLU_BG="\033[1;37;44m"

# print intro
echo -e 
echo -e "TESTER MINISHELL"
echo "----------------------------------------------"
echo -e "Inicio do teste $(date +"%d %B %Y") $(date +%R)"
echo -e "by $USER on $os os"
echo "----------------------------------------------"

# executa o make
MAKE_OUTPUT=$(make 2>&1)
MAKE_EXIT_CODE=$?

# verifica o make
if [ $MAKE_EXIT_CODE -ne 0 ]; then
	echo -e "${BLU_BG} Makefile ${RESET}   ===> ${RED}Erro: Make falhou: ${BOLD}TESTE CANCELADO.${RESET}"
	echo -e "$MAKE_OUTPUT"
	exit 1
else
	echo -e "${BLU_BG} Makefile ${RESET}   ===> ${GREEN}${BOLD}OK!${RESET}"
fi

# Verifica Norminette
NORMI_OUTPUT=$(find . | egrep ".*(\.c|\.h)$" | norminette)

if [[ $(echo "$NORMI_OUTPUT" | egrep -v "OK\!$") ]]; then
	echo -e "${BLU_BG} Norminette ${RESET} ===> ${RED}${BOLD}Erro:${RESET}"
	echo -e "$NORMI_OUTPUT" | egrep -v "OK\!$"
else
	echo -e "${BLU_BG} Norminette ${RESET} ===> ${GREEN}${BOLD}OK!${RESET}"
fi