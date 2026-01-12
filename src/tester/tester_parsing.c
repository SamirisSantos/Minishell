
/* ************************************************************************** */
/* */
/* tester.c (End-to-End Test for Minishell Parsing)                         */
/* */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <stdio.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

/* * ============================================================================
 * FUNÇÕES AUXILIARES DE IMPRESSÃO
 * ============================================================================
 */

void	print_token_type(t_token_type type)
{
	if (type == CMD) printf("CMD");
	else if (type == CMD_ARG) printf("ARG");
	else if (type == PIPE) printf(RED "PIPE" RESET);
	else if (type == REDIR_IN) printf(YELLOW "<" RESET);
	else if (type == REDIR_OUT) printf(YELLOW ">" RESET);
	else if (type == APPEND) printf(YELLOW ">>" RESET);
	else if (type == HEREDOC) printf(YELLOW "<<" RESET);
	else if (type == REDIR_IN_FILE) printf("IN_FILE");
	else if (type == REDIR_OUT_FILE) printf("OUT_FILE");
	else if (type == DELIMITER) printf("DELIM");
	else printf("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	printf(BLUE "  🔍 [TOKENS]: " RESET);
	if (!tokens)
	{
		printf("(null)\n");
		return ;
	}
	while (tokens)
	{
		printf("[");
		print_token_type(tokens->type);
		printf(": \"%s\"] -> ", tokens->data ? tokens->data : "NULL");
		tokens = tokens->next;
	}
	printf("NULL\n");
}

void	print_commands(t_cmd *cmds)
{
	int	i;
	int	count = 1;

	if (!cmds)
	{
		printf(RED "  ❌ [PARSER]: Nenhum comando gerado.\n" RESET);
		return ;
	}
	printf(GREEN "  🚀 [COMMANDS STRUCTURE]:\n" RESET);
	while (cmds)
	{
		printf("    📦 CMD #%d:\n", count++);
		
		// Args
		printf("       📂 ARGS: ");
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
			{
				printf("\"%s\"", cmds->args[i]);
				if (cmds->args[i + 1]) printf(", ");
				i++;
			}
		}
		else
			printf("(null)");
		printf("\n");

		// Redirects
		if (cmds->input_file)
			printf("       📥 INPUT: \"%s\" (Heredoc: %s)\n", 
				cmds->input_file, cmds->heredoc ? "SIM" : "NÃO");
		
		if (cmds->output_file)
			printf("       📤 OUTPUT: \"%s\" (Append: %s)\n", 
				cmds->output_file, cmds->append ? "SIM" : "NÃO");

		if (cmds->next)
			printf("       🔗 PIPE conecta com o próximo...\n");
		else
			printf("       🛑 FIM do Pipeline.\n\n");
		
		cmds = cmds->next;
	}
}

/* * ============================================================================
 * RUNNER DO TESTE
 * ============================================================================
 */

void	run_test(const char *raw_input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	char	*input;

	// Duplicamos porque o lexer/parser pode tentar dar free no input original
	input = ft_strdup(raw_input);
	
	printf("==============================================================\n");
	printf("🧪 INPUT: %s\"%s\"%s\n", CYAN, input, RESET);

	// 1. LEXER
	tokens = lexer(input);
	// print_tokens(tokens); // Descomente para ver tokens antes da expansão

	// 2. SYNTAX CHECK
	if (!syntax_check(tokens))
	{
		printf(RED "  🚫 SYNTAX ERROR DETECTED!\n" RESET);
		// Limpeza manual simplificada para o teste
		// free_all(tokens, NULL, input); 
		return ;
	}

	// 3. EXPANDER
	expand_tokens(tokens, shell);
	print_tokens(tokens); // Mostra tokens após expansão/limpeza de aspas

	// 4. PARSER
	cmds = parse_tokens(tokens);

	// 5. RESULTADO
	print_commands(cmds);

	// Limpeza (Certifique-se que free_all existe e funciona)
	// free_all(tokens, cmds, input);
}

int	main(void)
{
	t_shell	shell;
	
	// --- MOCK ENVIRONMENT ---
	// Criamos variáveis falsas para testar a expansão
	char *fake_env[] = {
		"USER=tester_bot",
		"HOME=/home/test",
		"VAR=expanded_value",
		"EMPTY=",
		"A=1",
		"B=2",
		NULL
	};

	shell.envp_cpy = fake_env;
	shell.exit_status = 42; // Para testar $?

	// --- CASOS DE TESTE ---

	// Básico
	run_test("ls -l -a", &shell);

	// Pipes
	run_test("cat file | grep error | wc -l", &shell);

	// Redirecionamentos
	run_test("grep 'pattern' < input.txt >> output.log", &shell);

	// Aspas e Expansão
	run_test("echo \"Ola $USER, exit code: $?\"", &shell);

	// Quote Removal (Remoção de Aspas)
	run_test("echo \"'aspas simples'\" '\"aspas duplas\"'", &shell);

	// Redirecionamento Complexo
	run_test("> outfile ls", &shell); // ls deve ir para args, outfile para output

	// Heredoc
	run_test("cat << EOF", &shell);

	// Erro de Sintaxe (Deve falhar graciosamente)
	run_test("ls | | wc", &shell);

	return (0);
}