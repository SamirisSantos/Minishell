/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:34:52 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/27 14:47:24 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
APAGAR | DEL
Extrair um palavra da string  de entrada,
teve lidar com as aspas,
ter cuidado com situacoes que sao aceitas como:
 exemplo "ec"ho isso 'e aceito no bash
 TESTE NO BASH
 - c2r1s4% "ec"ho name
 - c2r1s4% "e"cho name
 - c2r1s4% "ech"o name
 - c2r1s4% "echo" name
 -------  
c2r1s4% "echo name"
zsh: command not found: echo name
ESPACO DEPOIS DO COMANDO ECHO
c2r1s4% "echo      " name
zsh: command not found: echo      
c2r1s4% "echo " name     
zsh: command not found: echo 

OUTRO TESTE:
 DENTRO DAS ASPAS:
 - ESPACO ANTES DO ECHO TBM NAO ACEITA

*/

char	*extract_word(char **s)
{
	char	*start;
	char	quote_char;
	int		len;

	start = *s;
}