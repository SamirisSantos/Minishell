/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:09:59 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/25 11:40:33 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	quote_flag(char c, char *quote_char)
{
	if (*quote_char == 0)
		*quote_char = c;
	else if (*quote_char == c)
		*quote_char = 0;
}

char	*remove_quotes(char *str)
{
	char	*clean_str;
	char	quote_char;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	quote_char = 0;
	clean_str = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!clean_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"')
			&& (quote_char == 0 || str[i] == quote_char))
			quote_flag(str[i++], &quote_char);
		else
			clean_str[j++] = str[i++];
	}
	clean_str[j] = '\0';
	return (clean_str);
}
