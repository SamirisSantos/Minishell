#include "../../headers/minishell.h"

// ----------- MAIN TEST -----------

char *get_type_name(t_token_type type)
{
	if (type == CMD) return "CMD";
	if (type == CMD_ARG) return "CMD_ARG";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_IN_FILE) return "REDIR_IN_FILE";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == REDIR_OUT_FILE) return "REDIR_OUT_FILE";
    if (type == APPEND) return "APPEND";
	if (type == HEREDOC) return "HEREDOC";
	if (type == DELIMITER) return "DELIMITER";
	return "UNKNOWN";
}

void print_tokens(t_token *head)
{
	t_token *current = head;
	printf("\n--- RESULTADO DO LEXER ---\n");
	while (current)
	{
		printf("Tipo: %-15s | Valor: \"%s\"\n", get_type_name(current->type), current->data);
		current = current->next;
	}
	printf("--------------------------\n\n");
}

int main(void)
{
	char	*input;
	t_token *tokens;
	printf("🧪 BEM-VINDA AO TESTE DO LEXER 🧪\n");
	printf("Digite comandos para ver como o lexer os separa. (Ctrl+D para sair)\n\n");
	while (1)
	{
		input = readline("lexer_test$ ");
		if (!input) 
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		if (tokens)
		{
			print_tokens(tokens);
			free_tokens(tokens);
		}
		free(input);
	}
	return (0);
}
