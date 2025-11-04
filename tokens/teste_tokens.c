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

char	*extract_word(char **s);
int		is_space(char c);
int		is_metachar(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);

void test_line(const char *line_str)
{
	// Usamos strdup para criar uma cópia da string de teste.
	char *line_copy = ft_strdup(line_str);
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
		//Pular espaços em branco usando a função do projeto
		while (*ptr && is_space(*ptr))
			ptr++;
		
		if (!*ptr)
			break;
		if (is_metachar(*ptr))
		{
			printf("  [%d] Detectado Metachar: '%c'\n", i, *ptr);
			char op[2] = {*ptr, '\0'};
			printf("      -> (Simulando) Token Operador: \"%s\"\n", op);
			ptr++;
			printf("      -> Ponteiro restante: \"%s\"\n", ptr);
		}
		// Se não for metachar, é uma palavra
		else
		{
			printf("  [%d] Chamando extract_word em: \"%s\"\n", i, ptr);
			word = extract_word(&ptr);
			printf("      -> Extraído (Palavra): \"%s\"\n", word);
			printf("      -> Ponteiro restante: \"%s\"\n", ptr);
			free(word);
		}
		i++;
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
		"echo>out",                             // Colado no redirect
		"in<file",                              // Colado no redirect
		"cmd1|cmd2",                            // Colado no pipe
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