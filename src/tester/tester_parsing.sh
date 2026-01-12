#!/bin/bash

# --- CORES PARA FORMATACAO ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Limpa o terminal para ver melhor
clear

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}     🤖 MINISHELL PARSING TESTER 🤖      ${NC}"
echo -e "${BLUE}========================================${NC}"

# 1. Garante que estamos no diretório onde o script está salvo
# (Isso permite rodar o script de qualquer lugar, ex: ./src/tester/tester_first.sh)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo -e "${YELLOW}📂 Diretório: ${NC}$SCRIPT_DIR"

# 2. Compilação
echo -e "\n${YELLOW}🛠️  Compilando o projeto e o tester...${NC}"
make re

# Verifica se o comando 'make' deu erro (Exit Status != 0)
if [ $? -ne 0 ]; then
    echo -e "\n${RED}❌ ERRO FATAL: A compilação falhou!${NC}"
    echo -e "${RED}Verifique os erros acima e tente novamente.${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Compilação concluída com sucesso!${NC}"

# 3. Execução
echo -e "\n${YELLOW}▶️  Iniciando bateria de testes...${NC}"
echo -e "----------------------------------------\n"

./test_minishell

echo -e "\n----------------------------------------"
echo -e "${GREEN}🏁 Testes finalizados.${NC}"

# Opcional: Limpar os arquivos objeto depois de rodar
# echo -e "\n${YELLOW}🧹 Limpando arquivos objeto...${NC}"
# make clean