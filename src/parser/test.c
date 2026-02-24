#include "../../headers/minishell.h"

extern char **environ;

// --- MOCK SHELL (Igual ao anterior) ---
t_shell *init_mock_shell(void)
{
	t_shell *shell = malloc(sizeof(t_shell));
	if (!shell) return (NULL);
	shell->exit_status = 0;
	return (shell);
}

// --- VISUALIZADOR DO PARSER ---
void print_parser_result(t_cmd *cmd_list)
{
	t_cmd *current = cmd_list;
	int i = 0;
	int node_id = 1;

	printf("\n🏗️  RESULTADO DO PARSER (Estrutura t_cmd) 🏗️\n");
	printf("================================================\n");
	while (current)
	{
		printf("📦 NÓ %d:\n", node_id++);
		
		// 1. Argumentos (Onde args[0] é o comando)
		printf("   🔹 Args (Execve): [");
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("\"%s\"", current->args[i]);
				if (current->args[i + 1]) printf(", ");
				i++;
			}
		}
		printf("]\n");
		// 2. Redirecionamentos
		if (current->input_file)
			printf("   📥 Input File:    \"%s\" (Heredoc: %s)\n", 
				current->input_file, current->heredoc ? "SIM" : "NÃO");
		if (current->output_file)
			printf("   📤 Output File:   \"%s\" (Append: %s)\n", 
				current->output_file, current->append ? "SIM" : "NÃO");
		// 3. Pipe
		if (current->next)
			printf("   🔗 Pipe:          SIM (Conecta ao próximo nó)\n");
		else
			printf("   🛑 Pipe:          NÃO (Fim da linha)\n");
		printf("------------------------------------------------\n");
		current = current->next;
		}
		printf("\n");
}

int main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*commands;
	t_shell	*shell;

	shell = init_mock_shell();
	printf("🔧 TESTE INTEGRADO: LEXER -> EXPANDER -> PARSER 🔧\n");
	while (1)
	{
		input = readline("parser_test$ ");

		// 1. TRATAMENTO DO CTRL+D (EOF)
		if (!input) 
		{
			printf("exit (Ctrl+D detectado)\n");
			break;
		}
		// 2. TRATAMENTO DO COMANDO "exit"
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			printf("Saindo do teste... 👋\n");
			free(input);
			break;
		}
		if (*input)
		add_history(input);

		// --- EXECUÇÃO DO SHELL ---
		// 1. LEXER
		tokens = lexer(input);
		if (tokens)
		{
		// 2. EXPANDER
			expand_tokens(tokens, shell);
		// 3. PARSER (O foco de hoje!)
			if (is_syntax_valid(tokens)) 
			{
				commands = parse_tokens(tokens);
				print_parser_result(commands);
				free_commands(commands);
			}
			free_tokens(tokens);
		}
		free(input);
	}
	free(shell);
	return (0);
}