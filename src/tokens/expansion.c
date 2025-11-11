/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/11 17:45:39 by sade-ara         ###   ########.fr       */
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