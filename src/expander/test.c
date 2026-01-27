/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:35:00 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/27 17:18:05 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Cores para output
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

// IMPLEMENTAÇÃO LOCAL de free_array (para não depender de outros arquivos)
static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Função auxiliar para criar um token
t_token	*create_test_token(char *data, t_token_type type)
{
	char	*dup_data;
	t_token	*token;

	dup_data = ft_strdup(data);
	if (!dup_data)
		return (NULL);
	token = new_token(dup_data, type);
	return (token);
}

// Função auxiliar para criar um shell de teste
t_shell	*create_test_shell(char **envp)
{
	t_shell	*shell;
	int		i;
	int		count;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	
	// Contar variáveis de ambiente
	count = 0;
	while (envp[count])
		count++;
	
	// Copiar envp
	shell->envp_cpy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!shell->envp_cpy)
	{
		free(shell);
		return (NULL);
	}
	
	i = 0;
	while (i < count)
	{
		shell->envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp_cpy[i] = NULL;
	
	shell->exit_status = 0;
	shell->token = NULL;
	shell->tree = NULL;
	shell->xcmd = NULL;
	shell->cwd = NULL;
	shell->orig_input = NULL;
	
	return (shell);
}

// Função para imprimir tokens
void	print_tokens(t_token *token_list, const char *title)
{
	t_token	*current;
	int		i;

	printf("\n%s=== %s ===%s\n", BLUE, title, RESET);
	current = token_list;
	i = 0;
	while (current)
	{
		printf("Token %d: [%s] type=%d data=\"%s\"\n", 
			i, 
			current->type == CMD ? "CMD" :
			current->type == CMD_ARG ? "CMD_ARG" :
			current->type == REDIR_IN_FILE ? "REDIR_IN_FILE" :
			current->type == REDIR_OUT_FILE ? "REDIR_OUT_FILE" :
			current->type == DELIMITER ? "DELIMITER" :
			current->type == HEREDOC ? "HEREDOC" : "OTHER",
			current->type,
			current->data);
		current = current->next;
		i++;
	}
}

// Função de teste individual
void	run_test(char *test_name, t_shell *shell, t_token *token_list)
{
	printf("\n%s========================================%s\n", YELLOW, RESET);
	printf("%sTEST: %s%s\n", YELLOW, test_name, RESET);
	printf("%s========================================%s\n", YELLOW, RESET);
	
	print_tokens(token_list, "ANTES DA EXPANSÃO");
	
	expand_tokens(token_list, shell);
	
	print_tokens(token_list, "DEPOIS DA EXPANSÃO");
	
	free_tokens(token_list);
}

// TESTE 1: Expansão básica de variável
void	test_basic_expansion(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$USER", CMD_ARG));
	
	run_test("Expansão básica: echo $USER", shell, tokens);
}

// TESTE 2: Variável inexistente
void	test_nonexistent_var(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$NONEXISTENT", CMD_ARG));
	
	run_test("Variável inexistente: echo $NONEXISTENT", shell, tokens);
}

// TESTE 3: Exit status
void	test_exit_status(t_shell *shell)
{
	t_token	*tokens;
	
	shell->exit_status = 42;
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$?", CMD_ARG));
	
	run_test("Exit status: echo $? (com exit_status=42)", shell, tokens);
}

// TESTE 4: Aspas simples (não expandir)
void	test_single_quotes(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("'$USER'", CMD_ARG));
	
	run_test("Aspas simples: echo '$USER'", shell, tokens);
}

// TESTE 5: Aspas duplas (expandir)
void	test_double_quotes(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("\"$USER\"", CMD_ARG));
	
	run_test("Aspas duplas: echo \"$USER\"", shell, tokens);
}

// TESTE 6: Múltiplas variáveis
void	test_multiple_vars(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$USER$HOME", CMD_ARG));
	
	run_test("Múltiplas variáveis: echo $USER$HOME", shell, tokens);
}

// TESTE 7: $ isolado
void	test_isolated_dollar(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$", CMD_ARG));
	
	run_test("$ isolado: echo $", shell, tokens);
}

// TESTE 8: Variável com underscore
void	test_var_with_underscore(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$MY_VAR", CMD_ARG));
	
	run_test("Variável com _: echo $MY_VAR", shell, tokens);
}

// TESTE 9: Redirecionamento (deve expandir)
void	test_redirection(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("cat", CMD));
	add_token(&tokens, create_test_token("<", REDIR_IN));
	add_token(&tokens, create_test_token("$HOME/file.txt", REDIR_IN_FILE));
	
	run_test("Redirecionamento: cat < $HOME/file.txt", shell, tokens);
}

// TESTE 10: Heredoc delimiter (não deve expandir conteúdo, só remover aspas)
void	test_heredoc_delimiter(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("cat", CMD));
	add_token(&tokens, create_test_token("<<", HEREDOC));
	add_token(&tokens, create_test_token("\"EOF\"", DELIMITER));
	
	run_test("Heredoc delimiter: cat << \"EOF\"", shell, tokens);
}

// TESTE 11: Texto misto
void	test_mixed_text(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("Hello_$USER_World", CMD_ARG));
	
	run_test("Texto misto: echo Hello_$USER_World", shell, tokens);
}

// TESTE 12: Aspas mistas
void	test_mixed_quotes(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("\"$USER\"'$HOME'", CMD_ARG));
	
	run_test("Aspas mistas: echo \"$USER\"'$HOME'", shell, tokens);
}

// TESTE 13: Exit status com valores diferentes
void	test_exit_status_variations(t_shell *shell)
{
	t_token	*tokens;
	
	shell->exit_status = 127;
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$?", CMD_ARG));
	
	run_test("Exit status: echo $? (com exit_status=127)", shell, tokens);
	
	shell->exit_status = 0;
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("$?", CMD_ARG));
	
	run_test("Exit status: echo $? (com exit_status=0)", shell, tokens);
}

// TESTE 14: Variável vazia
void	test_empty_var(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = NULL;
	add_token(&tokens, create_test_token("echo", CMD));
	add_token(&tokens, create_test_token("antes$EMPTYdepois", CMD_ARG));
	
	run_test("Variável vazia: echo antes$EMPTYdepois", shell, tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		i;
	int		j;
	char	**new_envp;
	
	(void)argc;
	(void)argv;
	
	printf("\n%s╔════════════════════════════════════════╗%s\n", GREEN, RESET);
	printf("%s║  TESTE DO EXPANDER - MINISHELL 42     ║%s\n", GREEN, RESET);
	printf("%s╚════════════════════════════════════════╝%s\n", GREEN, RESET);
	
	// Criar shell de teste
	shell = create_test_shell(envp);
	if (!shell)
	{
		printf("%sERRO: Falha ao criar shell de teste%s\n", RED, RESET);
		return (1);
	}
	
	// Adicionar variável de teste ao ambiente
	i = 0;
	while (shell->envp_cpy[i])
		i++;
	
	// Realocar para adicionar MY_VAR e EMPTY
	new_envp = (char **)malloc(sizeof(char *) * (i + 3));
	if (!new_envp)
	{
		free_array(shell->envp_cpy);
		free(shell);
		return (1);
	}
	
	j = 0;
	while (j < i)
	{
		new_envp[j] = shell->envp_cpy[j];
		j++;
	}
	new_envp[j++] = ft_strdup("MY_VAR=test_value");
	new_envp[j++] = ft_strdup("EMPTY=");
	new_envp[j] = NULL;
	free(shell->envp_cpy);
	shell->envp_cpy = new_envp;
	
	// Executar testes
	test_basic_expansion(shell);
	test_nonexistent_var(shell);
	test_exit_status(shell);
	test_single_quotes(shell);
	test_double_quotes(shell);
	test_multiple_vars(shell);
	test_isolated_dollar(shell);
	test_var_with_underscore(shell);
	test_redirection(shell);
	test_heredoc_delimiter(shell);
	test_mixed_text(shell);
	test_mixed_quotes(shell);
	test_exit_status_variations(shell);
	test_empty_var(shell);
	
	// Liberar shell
	free_array(shell->envp_cpy);
	free(shell);
	
	printf("\n%s╔════════════════════════════════════════╗%s\n", GREEN, RESET);
	printf("%s║       TODOS OS TESTES CONCLUÍDOS       ║%s\n", GREEN, RESET);
	printf("%s╚════════════════════════════════════════╝%s\n\n", GREEN, RESET);
	
	return (0);
}