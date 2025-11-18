/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:34:52 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/18 12:41:29 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*extract_word(char **s)
{
	char	*start;
	char	quote_char;
	int		len;

	start = *s;
	len = 0;
	quote_char = 0;

	while (start[len])
	{
		if (is_quote(start[len]))
		{
			quote_char = start[len++];
			while (start[len] && start[len] != quote_char)
				len++;
			if (start[len] == quote_char)
				len++;
		}
		else if (is_space(start[len]) || is_metachar(start[len]))
			break;
		else
			len++;
	}
	*s += len;
	return (ft_substr(start, 0, len));
}
