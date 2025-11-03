//APAGAR | DEL
/*
 * =====================================
 *          FUNÇÃO DE TESTE 
 * =====================================
 */

#include "../headers/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void test_line(const char *line_str)
{
	// Usamos strdup para criar uma cópia da string de teste.
	// Embora extract_word não modifique o *conteúdo* da string,
	// o ponteiro 'ptr' será avançado.
	char *line_copy = strdup(line_str);
	if (!line_copy)
	{
		perror("strdup failed");
		return;
	}

	char *ptr = line_copy;
	char *word;
	int i = 1;

	printf("--- Testando Linha: \"%s\" ---\n", line_str);
	while (*ptr)
	{
		while (*ptr && isspace(*ptr))
			ptr++;
		if (!*ptr)
			break;
		printf("  [%d] Chamando extract_word em: \"%s\"\n", i, ptr);
		word = extract_word(&ptr);
		printf("      -> Extraído: \"%s\"\n", word);
		printf("      -> Ponteiro restante: \"%s\"\n", ptr);
		free(word);
		i++;
		if (word && *word == '\0' && (*ptr == '|' || *ptr == '<' || *ptr == '>')) {
			printf("      [AVISO] Detectado loop infinito potencial! Parando teste.\n");
			printf("      A função retornou \"\" mas o ponteiro não avançou de um delimitador.\n");
			break;
		}
	}
	printf("--- Fim do Teste: \"%s\" ---\n\n", line_str);
	free(line_copy);
}

int main(void)
{
	const char *test_cases[] = {
		"echo hello world",                     // Teste simples
		"ls -l",                                // Palavra com hífen
		"cmd   'palavra com espacos'  arg2",     // Aspas simples e espaços
		"cmd \"palavra com 'aspas' dentro\" ",  // Aspas duplas
		"echo 'aspas\"duplas\"misturadas'",     // Aspas misturadas
		"echo \"aspas'simples'misturadas\"",    // Aspas misturadas
		"palavra'junta'\"com\"aspas",            // Aspas coladas (deve ser 1 palavra)
		"ls | wc -l",                             // Teste de delimitador (pipe)
		"cat < infile > outfile",               // Teste de delimitadores (redirect)
		"<infile",                              // Delimitador no início
		"'quote nao fechada",                   // Aspas sem fechar
		"\"quote dupla nao fechada",            // Aspas duplas sem fechar
		"",                                     // String vazia
		"   ",                                  // Apenas espaços
		NULL                                    // Marcador de fim
	};

	int i = 0;
	while (test_cases[i])
	{
		test_line(test_cases[i]);
		i++;
	}
	return (0);
}
