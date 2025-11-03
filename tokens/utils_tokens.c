/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:09:00 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/03 14:58:25 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


/*
APAGAR | DEL
Lê um token tipo palavra até espaço ou operador
Trata operadores especiais (<, >, `)
Lê conteúdo dentro de ' ou "
Retorna o tipo de token com base no conteúdo
*/

// " \t\n\r\v\f" 
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
