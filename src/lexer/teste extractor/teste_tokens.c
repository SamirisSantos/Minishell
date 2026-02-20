//APAGAR | DEL
/*
 * =====================================
 *          FUNÇÃO DE TESTE 
 * =====================================
 */

#include "../../headers/minishell.h"
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
	char *ptr = line_copy;
	char *word;
	int i = 1;

	if (!line_copy)
	{
		perror("strdup failed");
		return;
	}
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
		// --- NOVOS TESTES REQUERIDOS ---
		"e\"c\"ho name",                             // "ec"ho name -> palavra: "echo"
		"\"e\"cho name",                            // "e"cho name -> palavra: "echo"
		"\"ec\"ho name",                            // "ec"ho name -> palavra: "echo"
		"\"ech\"o name",                            // "ech"o name -> palavra: "echo"
		"\"echo\" name",                            // "echo" name -> palavra: "echo"
		"echo\"\" hello",                           // echo"" hello -> palavra: "echo"
		"echo'' hello",                             // echo'' hello -> palavra: "echo"
		"'e'cho name",                              // 'e'cho name -> palavra: "echo"
		
		// --- TESTES DE LIMITE/COMPLEXOS ---
		"cmd   'palavra com espacos'  arg2",         // Aspas simples e espaços
		"cmd \"palavra com 'aspas' dentro\" ",      // Aspas duplas
		"palavra'junta'\"com\"aspas",                // Aspas coladas (deve ser 1 palavra)
		"echo 'aspas\"duplas\"misturadas'",         // Aspas misturadas
		"echo \"aspas'simples'misturadas\"",        // Aspas misturadas

		// --- TESTES DE OPERADORES/SEPARADORES ---
		"ls | wc -l",                               // Pipe
		"cat < infile > outfile",                   // Redirecionamentos
		"<infile",                                 // Redirecionamento no início
		"echo>out",                                 // Colado no redirect
		"in<file",                                  // Colado no redirect
		"cmd1|cmd2",                                // Colado no pipe
		
		// --- TESTES DE ERRO/ESPAÇOS ---
		"'quote nao fechada",                       // Aspas sem fechar (deve extrair tudo)
		"\"quote dupla nao fechada",                // Aspas duplas sem fechar (deve extrair tudo)
		"   ",                                      // Apenas espaços
		"",                                         // String vazia
		NULL                                        // Marcador de fim
	};

	int i = 0;
	while (test_cases[i])
	{
		test_line(test_cases[i]);
		i++;
	}
	return (0);
}