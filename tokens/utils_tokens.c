/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:09:00 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/27 14:47:49 by sade-ara         ###   ########.fr       */
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


