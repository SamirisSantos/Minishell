/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:29:34 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/23 17:13:45 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
Como funciona a leitura de uma linha de comando

cat file.txt | grep "error" > out.txt

t_comd 1:
  args: ["cat", "file.txt"]
  outfile_file: NULL
  next → t_command 2

t_comd 2:
  args: ["grep", "error"]
  outfile_file: "out.txt"
  append: 0
*/

// " \t\n\r\v\f" 
int	is_space(char *c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

// criar lista de tokens
t_token	*lexer(char *input)
{
	
}
