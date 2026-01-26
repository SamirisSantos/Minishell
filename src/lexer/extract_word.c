/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:34:52 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/26 16:53:54 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_quotes(char *s, int *len)
{
	char	quote;

	quote = s[(*len)++];
	while (s[*len] && s[*len] != quote)
		(*len)++;
	if (!s[*len])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (1);
	}
	(*len)++;
	return (0);
}

char	*extract_word(char **s)
{
	char	*start;
	int		len; 

	start = *s;
	len = 0;
	while (start[len])
	{
		if (is_quote(start[len]))
		{
			if (check_quotes(start, &len))
				return (NULL);
		}
		else if (is_space(start[len]) || is_metachar(start[len]))
			break;
		else
			len++;
	}
	*s += len;
	return (ft_substr(start, 0, len));
}
