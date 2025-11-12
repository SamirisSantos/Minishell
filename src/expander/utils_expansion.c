/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/12 16:08:54 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	get_env(char *name, char **envp)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 
				&& envp[i][len] == '=')
				return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*

APAGAR | DEL
exit_status
Sugestão do chat adicionar isso e fazer durante o Building
> ls                             # Comando 'ls' tem sucesso
minishell.h Makefile ...
> echo $?                        # Pergunta "Qual foi o status do último comando?"
0                                # O shell responde "0" (sucesso)

> ls ficheiro_que_nao_existe     # Este comando falha
ls: cannot access 'ficheiro_que_nao_existe': No such file or directory
> echo $?                        # Pergunta "Qual foi o status do último comando?"
2                                # O shell responde "2" (erro)
------

g_exit_status é a variável C que tu deves criar (provavelmente uma 
variável global, por isso o prefixo g_) para armazenar o código de 
saída do último comando que o teu Minishell executou.

Sempre que o teu executor corre um comando (seja um execve para ls 
ou um builtin como cd), ele recebe um código de saída. A tua lógica 
principal deve pegar nesse código (seja o status de um waitpid ou o 
return do teu builtin_cd) e guardá-lo nesta variável g_exit_status.

*/

/* APAGAR | DEL
	verificar qual o status exemplo
	exemplo
	minishell: echo name
	minishell: name
	minishell: $?
	minishell: 0;
	*/

static char	*get_var_value(char *str, char **envp, int *var_len)
{
	int		len;
	char	*name;
	char	*value;

	len = 0;
	if (str[i] == '?')
	{
		*var_len = 2;
		return(ft_itoa(g_exit_status)); // TODO 
	}
}

static void	process_var_len(char *str, char **envp, int *len, int *i)
{
	int		var_name_len;
	char	*val;

	// str[*i] é o mesmo que &str[i]
	val = get_var_value(&str[*i], envp, &var_name_len); 
	*len += ft_strlen(val);
	free(val);
	*i += var_name_len;
}

int	get_expanded_len(char *str, char **envp)
{
	int		i;
	int		len;
	int		var_len;
	char	quote;
	char	*val;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') 
			&& (quote == 0 || str[i] == quote))
			quote_flag(str[i++], &quote);
		else if (str[i] == '$' && quote != '\'')
			process_var_len(str, envp, &len, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
static void	process_var_fill(char *new_str, char *old_str, int *i, int *j, char **envp)
{
	int		var_len;
	char	*val;

	val = get_var_value(&old_str[*i], envp, &var_len);
	ft_strcpy(&new_str[*j], val);
	*j += ft_strlen(val);
	free(val);
	*i += var_len;
}

void	fill_expanded_str(char *new_str, char *old_str, char **envp)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (old_str[i])
	{
		if ((old_str[i] == '\'' || old_str[i] == '"')
			&& (quote == 0 || old_str[i] == quote))
			quote_flag(old_str[i++], &quote);
		else if (old_str[i] == '$' && quote != '\'')
		{
			process_var_fill(new_str, old_str, &i, &j, envp);
		}
		else
			new_str[j++] = old_str[i++];
	}
	new_str[j] = '\0';
}
